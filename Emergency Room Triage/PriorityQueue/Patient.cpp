/*
 * Name: Adnan Nassan.
 * Date: 2024-11-09.
 * Purpose of the file: Stores the implementation of the Patient class functions.
 */

#include "Patient.h"

// Constructors


Patient::Patient() : name_{}, counter_{} {}


Patient::Patient(std::string name) : name_(std::move(name)), counter_{} {
    if (name_.empty())
        throw std::invalid_argument("You should enter the patient name!");
}

void Patient::add_ailment(const Ailment& ailment) {
    ailments_.push_back(ailment);
    counter_++;
}

int Patient::get_score() const {
    int total = 0;
    LinkedList<Ailment>& nonConstAilments = const_cast<LinkedList<Ailment>&>(ailments_);
    auto ailment = nonConstAilments.begin();

    while (ailment != nullptr) {
        total += ailment->data.calculate_total_severity();
        ailment = ailment->next;
    }
    return total;
}


bool Patient::operator==(const Patient& other) const {
    return get_score() == other.get_score();
}


std::ostream& operator<<(std::ostream& os, const Patient& patient) {
    os << patient.get_name() << " - " << patient.get_score() << " - ";
    auto current = const_cast<LinkedList<Ailment>&>(patient.ailments_).begin();

    while (current != nullptr) {
        os << current->data.get_name() << ", ";
        current = current->next;
    }
    os << std::endl;
    return os;
}


