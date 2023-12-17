#include "persistor.hpp"

// static ptr
std::unique_ptr<Persistor> Persistor::instance = nullptr;

Persistor::Persistor(const std::string& eucalypt_grpc_address)
    : run_persistor_thread(true) {
  // set up connection to eucalypt
  chan_to_eucalypt = grpc::CreateChannel(eucalypt_grpc_address,
                                         grpc::InsecureChannelCredentials());
  eucalypt_stub = PersistorService::NewStub(chan_to_eucalypt);

  // start the thread that sends updates to Eucalypt
  persistor_thread = std::thread(&Persistor::send_events, this);
};

void Persistor::set_eucalypt_address(const std::string& eucalypt_grpc_address) {
  if (instance != nullptr) {
    throw std::runtime_error("Eucalypt grpc address already set.");
  }
  instance = std::unique_ptr<Persistor>(new Persistor(eucalypt_grpc_address));
}

std::unique_ptr<Persistor>& Persistor::get_instance() {
  if (instance == nullptr) {
    throw std::runtime_error("Eucalypt grpc address has not been set.");
  }
  return instance;
}

void Persistor::start_job(const StartJobEvent& start_job_event) {
  std::lock_guard<std::mutex> lock(persistor_lock);
  events.push_back(std::make_unique<StartJobEvent>(start_job_event));
}

void Persistor::start_task(const StartTaskEvent& start_task_event) {
  std::lock_guard<std::mutex> lock(persistor_lock);
  events.push_back(std::make_unique<StartTaskEvent>(start_task_event));
}

void Persistor::complete_event(const CompleteEvent& complete_event) {
  std::lock_guard<std::mutex> lock(persistor_lock);
  events.push_back(std::make_unique<CompleteEvent>(complete_event));
}

void Persistor::send_events() {
  while (run_persistor_thread) {
    sleep(3);  // persist updates every 3 seconds

    std::vector<std::unique_ptr<Event>> batch;
    persistor_lock.lock();
    std::swap(batch, events);
    persistor_lock.unlock();

    // std::cout << "Persistor thread has " << batch.size()
    //           << " updates to send to Eucalypt\n";

    for (const auto& event : batch)
      event->send_update(eucalypt_stub);
  }
}

Persistor::~Persistor() {
  // join the thread that sends events to Eucalypt on object destruction
  run_persistor_thread = false;
  persistor_thread.join();
}
