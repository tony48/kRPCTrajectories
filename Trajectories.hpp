#pragma once

#include <map>
#include <set>
#include <string>
#include <tuple>
#include <vector>

#include <krpc/decoder.hpp>
#include <krpc/encoder.hpp>
#include <krpc/error.hpp>
#include <krpc/event.hpp>
#include <krpc/object.hpp>
#include <krpc/service.hpp>
#include <krpc/stream.hpp>

namespace krpc {
namespace services {

class Trajectories : public Service {
 public:
  explicit Trajectories(Client* client);

  double get_impact_time();

  bool has_impact();

  std::tuple<double, double> impact_pos();

  ::krpc::Stream<double> get_impact_time_stream();

  ::krpc::Stream<bool> has_impact_stream();

  ::krpc::Stream<std::tuple<double, double>> impact_pos_stream();

  ::krpc::schema::ProcedureCall get_impact_time_call();

  ::krpc::schema::ProcedureCall has_impact_call();

  ::krpc::schema::ProcedureCall impact_pos_call();
};

}  // namespace services

namespace services {

inline Trajectories::Trajectories(Client* client):
  Service(client) {
}

inline double Trajectories::get_impact_time() {
  std::string _data = this->_client->invoke("Trajectories", "GetImpactTime");
  double _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline bool Trajectories::has_impact() {
  std::string _data = this->_client->invoke("Trajectories", "HasImpact");
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline std::tuple<double, double> Trajectories::impact_pos() {
  std::string _data = this->_client->invoke("Trajectories", "ImpactPos");
  std::tuple<double, double> _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline ::krpc::Stream<double> Trajectories::get_impact_time_stream() {
  return ::krpc::Stream<double>(this->_client, this->_client->build_call("Trajectories", "GetImpactTime"));
}

inline ::krpc::Stream<bool> Trajectories::has_impact_stream() {
  return ::krpc::Stream<bool>(this->_client, this->_client->build_call("Trajectories", "HasImpact"));
}

inline ::krpc::Stream<std::tuple<double, double>> Trajectories::impact_pos_stream() {
  return ::krpc::Stream<std::tuple<double, double>>(this->_client, this->_client->build_call("Trajectories", "ImpactPos"));
}

inline ::krpc::schema::ProcedureCall Trajectories::get_impact_time_call() {
  return this->_client->build_call("Trajectories", "GetImpactTime");
}

inline ::krpc::schema::ProcedureCall Trajectories::has_impact_call() {
  return this->_client->build_call("Trajectories", "HasImpact");
}

inline ::krpc::schema::ProcedureCall Trajectories::impact_pos_call() {
  return this->_client->build_call("Trajectories", "ImpactPos");
}
}  // namespace services

}  // namespace krpc
