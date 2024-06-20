#include <iostream>
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

public:
    PatientsLL() : head(nullptr){}

    PatientNode* findPatient(int patient_id) {
        PatientNode* current = head;
        while (current) {
            if (current->patient_id ==  patient_id)
                return current;
            current = current->next;
        }
        return nullptr;
    }

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

        cout << "Patient Registered successfully." << endl;
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

public:

    DoctorsLL(): head(nullptr){}

    DoctorNode* findDoctor(int doctor_id) {
        DoctorNode* current = head;
        while (current) {
            if (current->doctor_id ==  doctor_id)
                return current;
            current = current->next;
        }
        return nullptr;
    }
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

    void displayDoctors(){
        DoctorNode *node = head;
        while (node != nullptr){
            cout<<"Doctor ID: "<<node->doctor_id<<",  Name: "<<node->name<<",  Specialization: "<<node->specialization<<endl;
            node = node->next;
        }
    }
};

//Appointments Linked List
class AppointmentsLL{
private:
    AppointmentNode* head;

public:
    AppointmentsLL() : head(nullptr){}

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
        //check if appointment_id exists

        AppointmentNode* appointmentExists = this->finAppointment(appointment_id);
        if(appointmentExists != nullptr){
            cerr<<"Appointment with the same ID exists"<<endl;
            return;
        }

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

    void displayAppointments(){
        AppointmentNode* node = head;
        while (node != nullptr){
            cout<<"Appointment ID: "<<node->appointment_id<<",  Patient ID: "<<node->patient_id<<",  Doctor ID: "<<node->doctor_id<<",  Date: "<<node->appointment_date<<endl;
            node = node->next;
        }
    }
};

void display_menu(){
    cout<<"Menu: \n";
    cout<<"1. Register a patient\n";
    cout<<"2. Register a doctor \n";
    cout<<"3. Register an appointment\n";
    cout<<"4. Display Patients\n";
    cout<<"5. Display Doctors\n";
    cout<<"6. Display Appointments\n";
    cout<<"7. Exit\n";
}

int main() {

    PatientsLL patientsLinkedList;
    DoctorsLL doctorsLinkedList;
    AppointmentsLL appointmentsLinkedlist;

    while (true){
        display_menu();
        int choice;
        cout << "Enter your choice: ";
        cin>>choice;

        if(choice == 1){
            int id;
            string name, dob, gender;
            cout<<"ID: ";
            cin>>id;

            //check if ID exists
            PatientNode *patient_exists = patientsLinkedList.findPatient(id);
            while (patient_exists != nullptr){
                cerr<<"Patient with the same exists, try again:"<<endl;
                cout<<"ID: ";
                cin>>id;
                patient_exists = patientsLinkedList.findPatient(id);
            }
            cout<<"Name: ";
            cin>>name;
            cout<<"DOB: ";
            cin>>dob;
            cout<<"Gender: ";
            cin>>gender;
            patientsLinkedList.addPatient(id, name, dob,gender);
        }else if (choice == 2){
            int id;
            string name, specialization;
            cout<<"ID: ";
            cin>>id;

            //check if ID exists
            DoctorNode *doctor_exists = doctorsLinkedList.findDoctor(id);
            while (doctor_exists != nullptr){
                cerr<<"Doctor with the same exists, try again:"<<endl;
                cout<<"ID: ";
                cin>>id;
                doctor_exists = doctorsLinkedList.findDoctor(id);
            }
            cout<<"Name: ";
            cin>>name;
            cout<<"Specialization: ";
            cin>>specialization;
            doctorsLinkedList.addDoctor(id, name, specialization);
        }else if(choice == 3) {
            int id, patient_id, doctor_id;
            string date;
            cout<<"ID: ";
            cin>>id;

            //check if ID exists
            AppointmentNode *appointment_exists = appointmentsLinkedlist.finAppointment(id);
            while (appointment_exists != nullptr){
                cerr<<"Appointment with the same exists, try again: "<<endl;
                cout<<"ID: ";
                cin>>id;
                appointment_exists = appointmentsLinkedlist.finAppointment(id);
            }
            cout<<"P_ID: ";
            cin>>patient_id;

            cout<<"D_ID: ";
            cin>>doctor_id;

            //check if patient_id exists
            PatientNode* patient_exists = patientsLinkedList.findPatient(patient_id);
            //check if doctor_id exists
            DoctorNode* doctor_exists = doctorsLinkedList.findDoctor(doctor_id);

            if(patient_exists == nullptr){
                cerr<<"[FAILED] Patient ID does not exist"<<endl;
            }
            if(doctor_exists == nullptr){
                cerr<<"[FAILED] Doctor ID does not exist"<<endl;
            }

            if(patient_exists == nullptr || doctor_exists == nullptr){
                continue;
            }

            cout<<"DATE: ";
            cin>>date;
            appointmentsLinkedlist.addAppointment(id, doctor_id, patient_id, date);
        }else if(choice == 4){
            patientsLinkedList.displayPatients();
        }else if(choice == 5){
            doctorsLinkedList.displayDoctors();
        }else if(choice == 6){
            appointmentsLinkedlist.displayAppointments();
        }else if(choice == 7){
            break;
        }else{
            cout<<"Invalid input choice"<<endl;
        }
    }
}
