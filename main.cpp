#include <iostream>
#include <algorithm>
#include <fstream>
#include <limits>

using namespace std;

#define PATIENTS_FILE "patients.csv"
#define DOCTORS_FILE "doctors.csv"
#define APPOINTMENTS_FILE "appointments.csv"

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

    void saveToCSV(const string& fileName) {
        ofstream file(fileName);
        if (file.is_open()) {
            file << "ID,Name,DOB,Gender\n";
            PatientNode* current = head;
            while (current) {
                file << current->patient_id << "," << current->name << "," << current->dob << ","<<current->gender<<"\n";
                current = current->next;
            }
            file.close();
            cout << "Patients information saved to " << fileName << "." << endl;
        } else {
            cout << "Unable to open file." << endl;
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

    void saveToCSV(const string& fileName) {
        ofstream file(fileName);
        if (file.is_open()) {
            file << "ID,Name,Specialization,Gender\n";
            DoctorNode* current = head;
            while (current) {
                file << current->doctor_id << "," << current->name << "," << current->specialization << ","<<"\n";
                current = current->next;
            }
            file.close();
            cout << "Doctors information saved to " << fileName << "." << endl;
        } else {
            cout << "Unable to open file." << endl;
        }
    }
};

//Appointments Linked List
class AppointmentsLL{
private:
    AppointmentNode* head;

public:
    AppointmentsLL() : head(nullptr){}

    AppointmentNode* finAppointment(int appointment_id) { //find by id
        AppointmentNode* current = head;
        while (current) {
            if (current->appointment_id ==  appointment_id)
                return current;
            current = current->next;
        }
        return nullptr;
    }
    void addAppointment( int appointment_id, int doctor_id, int patient_id, string appointment_date){ //add a new appointment
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

    void displayAppointments(){ //display appointments
        AppointmentNode* node = head;
        while (node != nullptr){
            cout<<"Appointment ID: "<<node->appointment_id<<",  Patient ID: "<<node->patient_id<<",  Doctor ID: "<<node->doctor_id<<",  Date: "<<node->appointment_date<<endl;
            node = node->next;
        }
    }

    void saveToCSV(const string& fileName) { //save the info to a csv file
        ofstream file(fileName);
        if (file.is_open()) {
            file << "ID,Patient_ID,Doctor_ID,Date\n";
            AppointmentNode* current = head;
            while (current) {
                file << current->appointment_id << "," << current->patient_id << "," << current->doctor_id << ","<<current->appointment_date<<"\n";
                current = current->next;
            }
            file.close();
            cout << "Appointments information saved to " << fileName << "." << endl;
        } else {
            cout << "Unable to open file." << endl;
        }
    }
};

void display_menu(){ //menu
    cout<<"Menu: \n";
    cout<<"1. Register a patient\n";
    cout<<"2. Register a doctor \n";
    cout<<"3. Register an appointment\n";
    cout<<"4. Display Patients\n";
    cout<<"5. Display Doctors\n";
    cout<<"6. Display Appointments\n";
    cout<<"7. Exit\n\n";
}

void display_welcome(){ // welcome message
    cout<<" _______________________________________________________________________"<<endl;
    cout<<"|                                                                       |"<<endl;
    cout<<"|         RUHENGERI REFERRAL HOSPITAL | APPOINTMENTS SYSTEM             |"<<endl;
    cout<<"|                                                                       |"<<endl;
    cout<<"| _____________________________________________________________________ |\n\n"<<endl;
}

void check_number_input(int &num){
    while(true)
    {
        if(cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cerr<<"input must be a number: "<<endl;
            cin>>num;
        }
        if(!cin.fail())
            break;
    }
}

int main() {
    display_welcome();
    PatientsLL patientsLinkedList;
    DoctorsLL doctorsLinkedList;
    AppointmentsLL appointmentsLinkedlist;

    while (true){
        display_menu();
        int choice;
        cout << "Enter your choice: ";
        cin>>choice;

        check_number_input(choice);

        // I used IF ELSE instead of switch because of c++ switch jump bypasses variable initialization error [I declare other variables inside the switch statements]
        if(choice == 1){
            int id;
            string name, dob, gender;
            cout<<"ID: ";
            cin>>id;
            check_number_input(id);

            //check if ID exists
            PatientNode *patient_exists = patientsLinkedList.findPatient(id);
            while (patient_exists != nullptr){
                cerr<<"Patient with the same exists, try again:"<<endl;
                cout<<"ID: ";
                cin>>id;
                patient_exists = patientsLinkedList.findPatient(id);
            }
            cin.ignore(1,'\n');
            cout<<"Name: ";
            getline(cin, name);
            cout<<"DOB: ";
            getline(cin, dob);
            cout<<"Gender: ";
            getline(cin, gender);
            patientsLinkedList.addPatient(id, name, dob,gender);
        }else if (choice == 2){
            int id;
            string name, specialization;
            cout<<"ID: ";
            cin>>id;
            check_number_input(id);
            //check if ID exists
            DoctorNode *doctor_exists = doctorsLinkedList.findDoctor(id);
            while (doctor_exists != nullptr){
                cerr<<"Doctor with the same exists, try again:"<<endl;
                cout<<"ID: ";
                cin>>id;
                doctor_exists = doctorsLinkedList.findDoctor(id);
            }
            cin.ignore(1,'\n');
            cout<<"Name: ";
            getline(cin, name);
            cout<<"Specialization: ";
            getline(cin, specialization);
            doctorsLinkedList.addDoctor(id, name, specialization);
        }else if(choice == 3) {
            int id, patient_id, doctor_id;
            string date;
            cout<<"ID: ";
            cin>>id;
            check_number_input(id);
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
            check_number_input(patient_id);
            cout<<"D_ID: ";
            cin>>doctor_id;
            check_number_input(doctor_id);
            cin.ignore(1,'\n');
            cout<<"DATE: ";
            getline(cin, date);
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
            appointmentsLinkedlist.addAppointment(id, doctor_id, patient_id, date);
        }else if(choice == 4){
            patientsLinkedList.displayPatients();
        }else if(choice == 5){
            doctorsLinkedList.displayDoctors();
        }else if(choice == 6){
            appointmentsLinkedlist.displayAppointments();
        }else if(choice == 7){
            cout<<"Saving information to .csv files"<<endl;
            patientsLinkedList.saveToCSV(PATIENTS_FILE);
            doctorsLinkedList.saveToCSV(DOCTORS_FILE);
            appointmentsLinkedlist.saveToCSV(APPOINTMENTS_FILE);
            break;
        }else{
            cout<<"Invalid input choice"<<endl;
        }
    }
}
