/*
*   Public Interface lib koala
*/

#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <vector>

// Macro that loads an instance of a mapper into a static dictionary
#define REGISTER_MAPPER(t) \
  t _mapper##t;            \
  bool _b##t = map_reduce::register_mapper(#t, &_mapper##t);

// Macro that loads an instance of a reducer into a static dictionary
#define REGISTER_REDUCER(t) \
  t _reducer##t;            \
  bool _b##t = map_reduce::register_reducer(#t, &_reducer##t);

namespace map_reduce {
// User should extend this base mapper
class Mapper {
 protected:
  void emit(const std::string& key, const std::string& value);

 public:
  Mapper();

  // pimpl pattern, so that we can hide that values emitted with emit() end up being distributed among the intermediary files
  struct impl;
  std::unique_ptr<impl> pImpl;

  virtual void map(const std::string& line) = 0;

  virtual ~Mapper();
};

class ValueIterator {
 private:
  std::string current_key;
  std::optional<std::string> current_value;
  std::function<std::optional<std::string>()> ask_for_value;

 public:
  ValueIterator(
      const std::string& key,
      const std::function<std::optional<std::string>()>& ask_for_value);

  bool has_next();

  std::string get();

  ~ValueIterator();
};

// User should extend this base reducer
class Reducer {
 protected:
  void emit(const std::string& key, const std::string& value);

 public:
  Reducer();

  // pimpl pattern
  struct impl;
  std::unique_ptr<impl> pImpl;

  virtual void reduce(const std::string& key, ValueIterator& iter) = 0;

  virtual ~Reducer();
};

bool register_mapper(const std::string& name, Mapper* mapper);
bool register_reducer(const std::string& name, Reducer* reducer);

void init(int argc, char** argv);

using job_uuid = std::string;

job_uuid register_job(const std::string& mapper_name,
                      const std::string& reducer_name,
                      const std::string& file_regex, int R,
                      const std::string& token = "");
void join_job(const job_uuid& job);
};  // namespace map_reduce
