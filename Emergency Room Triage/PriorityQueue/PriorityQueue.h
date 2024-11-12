/*
 * Name: Adnan Nassan.
 * Date: 2024-09-11.
 * Purpose of the file: Stores the declaration and implementation of the PriorityQueue class.
 */

#pragma once
#include "LinkedList.h"
#include <iostream>

template <typename T>
class PriorityQueue {
    LinkedList<T> patients_;
    unsigned count = 0;

public:
    /**
     * \fn PriorityQueue()
     * \brief Default constructor initializes an empty priority queue.
     * \author Adnan Nassan
     * \date November 06, 2024
     */
    PriorityQueue() {}

    /**
     * \fn auto get_patients_list() const
     * \brief Retrieves the list of patients.
     * \return A copy of the patients LinkedList.
     * \author Adnan Nassan
     * \date November 06, 2024
     */
    auto get_patients_list() const {
        return patients_;
    }

    /**
     * \fn bool empty() const
     * \brief Checks if the queue is empty.
     * \return True if the queue is empty, otherwise false.
     * \author Adnan Nassan
     * \date November 06, 2024
     */
    bool empty() const { return patients_.empty(); }

    /**
     * \fn int size() const
     * \brief Returns the number of patients in the queue.
     * \return The size of the queue.
     * \author Adnan Nassan
     * \date November 06, 2024
     */
    int size() const { return patients_.size(); }

    /**
     * \fn void sort_priority()
     * \brief Sorts the queue based on patient priority using bubble sort.
     * \author Adnan Nassan
     * \date November 06, 2024
     */
    void sort_priority() {
        if (patients_.empty()) return;

        bool swapped;
        do {
            swapped = false;
            auto current = patients_.begin();

            while (current->next != nullptr) {
                if (current->data.get_score() < current->next->data.get_score()) {
                    std::swap(current->data, current->next->data);
                    swapped = true;
                }
                current = current->next;
            }
        } while (swapped);
    }

    /**
     * \fn void enqueue(const T& patient)
     * \brief Adds a patient to the queue based on priority.
     * \param patient The patient to add.
     * \author Adnan Nassan
     * \date November 06, 2024
     */
    void enqueue(const T& patient) {
        patients_.push_back(patient);
        sort_priority();
    }

    /**
     * \fn T dequeue()
     * \brief Removes and returns the highest-priority patient from the queue.
     * \throws std::runtime_error if the queue is empty.
     * \return The highest-priority patient.
     * \author Adnan Nassan
     * \date November 06, 2024
     */
    T dequeue() {
        if (empty()) {
            throw std::runtime_error("Attempted to dequeue from an empty queue.");
        }
        return patients_.pop_front();
    }

    /**
     * \fn void displayPatients()
     * \brief Displays all patients in the queue, including their details.
     * \author Adnan Nassan
     * \date November 06, 2024
     */
    void displayPatients() {
        if (patients_.empty()) {
            std::cout << "The queue is currently empty. No patients to display.\n";
            return;
        }
        std::cout << "Patients In Queue: "<<std::endl;
        auto current = patients_.begin();
        int counter = 0;
        while (current != nullptr) {
            std::cout << counter << ": " << current->data;
            current = current->next;
            counter++;
        }
    }

    /**
     * \fn void find_patient_in_queue()
     * \brief Finds and displays the patient with the highest priority in the queue.
     * \throws std::runtime_error if the queue is empty.
     * \author Adnan Nassan
     * \date November 06, 2024
     */
    void find_next_patient_in_queue() {
        if (empty()) {
            std::cerr << "No patients in the queue." << std::endl;
            return;
        }

        auto patient = patients_.begin()->data;
        std::cout << "Next in queue: " << patient.get_name() << " with priority score " << patient.get_score() << std::endl;
    }    


    /**
 * \fn bool find_patient_by_name(const std::string& name) const
 * \brief Checks if a patient with a given name exists in the queue.
 * \param name The name of the patient to search for.
 * \return True if the patient exists in the queue, false otherwise.
 * \author Adnan Nassan
 * \date November 06, 2024
 */
    bool find_patient_by_name(const std::string& name) const {
        LinkedList<T>& nonConstPatients = const_cast<LinkedList<T>&>(patients_);
        auto current = nonConstPatients.begin();

        while (current != nullptr) {
            if (current->data.get_name() == name) {
                return true; // Patient found
            }
            current = current->next;
        }
        return false; // Patient not found
    }
};
