// DataFromRunOrService
//
// A utility templated function to get data either from the Run record or from
// a service. The run record is tried first. If that fails and the service does not
// exist, then an exception is thrown.
//
// 

#ifndef DATAFROMRUNORSERVICE_HH
#define DATAFROMRUNORSERVICE_HH

#include <string>

namespace artg4 {
  
  template <typename DATATYPE,
            typename SERVICETYPE >
  
  const DATATYPE& dataFromRunOrService(const std::string)
  
  
}

#endif
