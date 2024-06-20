#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <algorithm>

using namespace std;

//NODES
//Patient Node
class PatientNode {
public:
    int patient_id;
    string name;
    string dob;
    string gender;
    PatientNode* next;

    PatientNode(int patientId, const string &name, const string &dob, const string &gender)
            : patient_id(patientId), name(name), dob(dob), gender(gender), next(nullptr) {}
};

//Doctor Node
class DoctorNode{
public:
    int doctor_id;
    string name;
    string specialization;
    DoctorNode* next;

    DoctorNode(int doctorId, const string &name, const string &specialization)
            : doctor_id(doctorId),name(name),specialization(specialization),next(nullptr) {}

};

//Appointment Node

class AppointmentNode{
public:
    int appointment_id;
    int patient_id;
    int doctor_id;
    string appointment_date;
    AppointmentNode* next;

    AppointmentNode(int appointmentId, int patientId, int doctorId, string appointmentDate) : appointment_id(
            appointmentId), patient_id(patientId), doctor_id(doctorId), appointment_date(appointmentDate), next(nullptr) {}

};


//LinkedLists

//patients Linked List
class PatientsLL{
private:
    PatientNode* head;
    PatientNode* findPatient(int patient_id) {
        PatientNode* current = head;
        while (current) {
            if (current->patient_id ==  patient_id)
                return current;
            current = current->next;
        }
        return nullptr;
    }

public:
    PatientsLL() : head(nullptr){}

    void addPatient(int patient_id, string name, string dob, string gender){
        //check if the id is taken
        PatientNode* patientExists = this->findPatient(patient_id);
        if(patientExists != nullptr){
            cerr<<"Patient with the same id already exists"<<endl;
            return;
        }

        PatientNode* newPatient = new PatientNode(patient_id, name, dob, gender);

        if(!head){
            head = newPatient;
        }else{
            PatientNode* current = head;
            while (current->next){
                current = current->next;
            }
            current->next = newPatient;
        }

        cout << "Patient " << name << " added successfully." << endl;
    }

    void displayPatients(){
        PatientNode *node = head;
        while (node != nullptr){
            cout<<"Patient ID: "<<node->patient_id<<",  Name: "<<node->name<<",  DOB: "<<node->dob<<",  Gender: "<<node->gender<<endl;
            node = node->next;
        }
    }
};

//Doctors
class DoctorsLL{
private:
    DoctorNode* head;
    DoctorNode* findDoctor(int doctor_id) {
        DoctorNode* current = head;
        while (current) {
            if (current->doctor_id ==  doctor_id)
                return current;
            current = current->next;
        }
        return nullptr;
    }
public:
    DoctorsLL(): head(nullptr){}

    void addDoctor(int doctor_id, string name, string specialization){
        // check if the id is taken
        DoctorNode* doctorExists = this->findDoctor(doctor_id);
        if(doctorExists != nullptr){
            cerr<<"Doctor with the same ID exists"<<endl;
            return;
        }

        DoctorNode* newDoctor = new DoctorNode(doctor_id, name, specialization);

        if(!head){
            head = newDoctor;
        }else{
            DoctorNode* current = head;
            while(current->next){
                current = current->next;
            }
            current->next = newDoctor;
        }
        cout<<"Doctor registered successfully"<<endl;
    }

    void listDoctors(){
        DoctorNode *node = head;
        while (node != nullptr){
            cout<<"Doctor ID: "<<node->doctor_id<<",  Name: "<<node->name<<",  Specialization: "<<node->specialization<<endl;
        }
    }
};

//Appointments Linked List
class AppointmentsLL{
private:
    AppointmentNode* head;
    AppointmentNode* finAppointment(int appointment_id) {
        AppointmentNode* current = head;
        while (current) {
            if (current->appointment_id ==  appointment_id)
                return current;
            current = current->next;
        }
        return nullptr;
    }

    void addAppointment( int appointment_id, int doctor_id, int patient_id, string appointment_date){
        //check if both doctor_id and patient_id exists

        //create appointment
        AppointmentNode* newAppointment = new AppointmentNode(appointment_id, patient_id, doctor_id, appointment_date);

        if(!head){
            head = newAppointment;
        }else{
            AppointmentNode* current = head;
            while (current->next){
                current = current->next;
            }
            current->next = newAppointment;
        }
        cout << "Appointment registered successfully"<<endl;
    }

    void listAppointments(){
        AppointmentNode* node = head;
        while (node != nullptr){
            cout<<"Appointment ID: "<<node->appointment_id<<",  Patient ID: "<<node->patient_id<<",  Doctor ID: "<<node->doctor_id<<",  Date: "<<node->appointment_date<<endl;
            node = node->next;
        }
    }
};

int main() {
    cout << "HEALTH SYSTEM!" << endl;
    return 0;
}
