/*
*   Public Interface lib koala
*/

#include <string>

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
 public:
  virtual void map() = 0;
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
                  const std::string& file_regex);
};  // namespace map_reduce
