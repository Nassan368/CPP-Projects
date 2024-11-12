/*
 * Name: Adnan Nassan.
 * Date: 2024-09-11.
 * Purpose of the file: Stores the implementation of the Ailment class functions.
 */
#include "Ailment.h"


Ailment::Ailment() : name_(""), severity_(0), time_criticality_(0), contagiousness_(0) {}


Ailment::Ailment(std::string name, int severity, int time_criticality, int contagiousness)
    : name_(std::move(name)), severity_(severity), time_criticality_(time_criticality), contagiousness_(contagiousness) {}


Ailment::~Ailment() {}


int Ailment::calculate_total_severity() const {
    return (severity_ * time_criticality_) + contagiousness_;
}


bool Ailment::operator==(const Ailment& other) const {
    return calculate_total_severity() == other.calculate_total_severity();
}


std::ostream& operator<<(std::ostream& os, const Ailment& ailment) {
    os << ailment.get_name() << ","
        << ailment.get_severity() << ","
        << ailment.get_time_sensitivity() << ","
        << ailment.get_contagiousness();
    return os;
}
