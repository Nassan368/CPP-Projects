
/*
 * Name: Adnan Nassan.
 * Date: 2024-09-11.
 * Purpose of the file: Stores the declaration of the Ailment class and its functions.
 */
#pragma once

#include <string>
#include <iostream>
#include <stdexcept>

/**
 * \class Ailment
 * \brief Represents a medical ailment with attributes such as name, severity, time criticality, and contagiousness.
 * \author Adnan Nassan
 * \date November 06, 2024
 */
class Ailment {
    std::string name_;
    int severity_;
    int time_criticality_;
    int contagiousness_;

public:
 
    //Constructers
    Ailment();
    Ailment(std::string name, int severity, int time_criticality, int contagiousness);
    ~Ailment();

    //Getters
    std::string get_name() const { return name_; }
    int get_severity() const { return severity_; }
    int get_time_sensitivity() const { return time_criticality_; }
    int get_contagiousness() const { return contagiousness_; }

    /**
     * \fn int calculate_total_severity() const
     * \brief Calculates the priority score of the ailment.
     * \return The calculated severity score.
     * \author Adnan Nassan
     * \date November 06, 2024
     */
    int calculate_total_severity() const;

    /**
     * \fn bool operator==(const Ailment& other) const
     * \brief Compares two ailments by their severity scores.
     * \param other Another ailment to compare with.
     * \return True if severity scores are equal; otherwise, false.
     * \author Adnan Nassan
     * \date November 06, 2024
     */
    bool operator==(const Ailment& other) const;

    /**
     * \fn friend std::ostream& operator<<(std::ostream& os, const Ailment& ailment)
     * \brief Overloads the stream insertion operator to output ailment details.
     * \param os Output stream.
     * \param ailment Ailment object to output.
     * \return The output stream with ailment details appended.
     * \author Adnan Nassan
     * \date November 06, 2024
     */
    friend std::ostream& operator<<(std::ostream& os, const Ailment& ailment);
};
