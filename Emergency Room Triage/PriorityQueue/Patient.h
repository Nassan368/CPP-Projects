/*
 * Name: Adnan Nassan.
 * Date: 2024-09-11.
 * Purpose of the file: Stores the declaration of the Patient class and its functions.
 */

#pragma once
#include "Ailment.h"
#include "LinkedList.h"
#include <string>
#include <iostream>
#include <ostream>
#include <stdexcept>


class Patient {
    std::string name_;
    LinkedList<Ailment> ailments_;
    int counter_;

public:

    Patient();

    ~Patient() {};
    Patient(std::string name);

   
    std::string get_name() const { return name_; }

 
    auto get_ailments() const { return ailments_; }

    /**
     * \fn int get_score() const
     * \brief Calculates and returns the total priority score based on the patient's ailments.
     * \return The total priority score.
     * \author Adnan Nassan
     * \date November 06, 2024
     */
    int get_score() const;

    /**
     * \fn int get_number_of_ailment() const
     * \brief Returns the number of ailments the patient has.
     * \return The number of ailments.
     */
    int get_number_of_ailment() const { return counter_; }

    /**
     * \fn void add_ailment(const Ailment& ailment)
     * \brief Adds an ailment to the patient's list and increments the ailment counter.
     * \param ailment The ailment to add.
     * \author Adnan Nassan
     * \date November 06, 2024
     */
    void add_ailment(const Ailment& ailment);

    /**
     * \fn bool operator==(const Patient& other) const
     * \brief Compares two patients based on their priority scores.
     * \param other Another patient to compare with.
     * \return True if the scores are equal, false otherwise.
     */
    bool operator==(const Patient& other) const;

    /**
     * \fn friend std::ostream& operator<<(std::ostream& os, const Patient& patient)
     * \brief Overloads the stream insertion operator to output patient details.
     * \param os Output stream.
     * \param patient Patient object to output.
     * \return The output stream with patient details appended.
     */
    friend std::ostream& operator<<(std::ostream& os, const Patient& patient);
};
