/*
*   Public Interface lib koala
*/

#include <memory>
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

  // pimpl pattern, so that we can hide that vales emitted with emit() end up being distributed among the intermediary files
  struct impl;
  std::unique_ptr<impl> pImpl;

  virtual void map(const std::string& line) = 0;

  ~Mapper();
};

// User should extend this base reducer
class Reducer {
 public:
  virtual void reduce() = 0;
};

bool register_mapper(const std::string& name, Mapper* mapper);
bool register_reducer(const std::string& name, Reducer* reducer);

void init(int argc, char** argv);

void register_job(const std::string& mapper_name,
                  const std::string& reducer_name,
                  const std::string& file_regex, int R,
                  const std::string& email = "",
                  const std::string& token = "");
};  // namespace map_reduce
