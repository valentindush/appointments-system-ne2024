#include <iostream>
#include <algorithm>
#include <fstream>
#include <limits>
#include <sstream>
#include <regex>

using namespace std;

//FILE PATHS
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

    PatientNode* findPatient(int patient_id) { //find patient
        PatientNode* current = head;
        while (current) {
            if (current->patient_id ==  patient_id)
                return current;
            current = current->next;
        }
        return nullptr;
    }

    void addPatient(int patient_id, string name, string dob, string gender){ //add patient
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

    void displayPatients(){ // display patients
        PatientNode *node = head;
        while (node != nullptr){
            cout<<"Patient ID: "<<node->patient_id<<",  Name: "<<node->name<<",  DOB: "<<node->dob<<",  Gender: "<<node->gender<<endl;
            node = node->next;
        }
    }

    void saveToCSV(const string& fileName) { //save patients to csv file
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

    void loadFromCSV(const string& fileName) { //load patients from csv file
        ifstream file(fileName);
        if (file.is_open()) {
            string line;
            getline(file, line); // Skip header
            while (getline(file, line)) {
                stringstream ss(line);
                string id_str, name, dob, gender;
                getline(ss, id_str, ',');
                getline(ss, name, ',');
                getline(ss, dob, ',');
                getline(ss, gender, ',');
                int id = stoi(id_str);
                addPatient(id, name, dob, gender);
            }
            file.close();
            cout << "Patients data loaded from " << fileName << "." << endl;
        } else {
            cout << "No existing patients data file found. Starting with empty list." << endl;
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
    void addDoctor(int doctor_id, string name, string specialization){ //add a new doctor
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

    void displayDoctors(){ //display all doctors
        DoctorNode *node = head;
        while (node != nullptr){
            cout<<"Doctor ID: "<<node->doctor_id<<",  Name: "<<node->name<<",  Specialization: "<<node->specialization<<endl;
            node = node->next;
        }
    }

    void saveToCSV(const string& fileName) { //save doctors to csv
        ofstream file(fileName);
        if (file.is_open()) {
            file << "ID,Name,Specialization\n";
            DoctorNode* current = head;
            while (current) {
                file << current->doctor_id << "," << current->name << "," << current->specialization << "\n";
                current = current->next;
            }
            file.close();
            cout << "Doctors information saved to " << fileName << "." << endl;
        } else {
            cout << "Unable to open file." << endl;
        }
    }

    void loadFromCSV(const string& fileName) { //load doctors from csv file
        ifstream file(fileName);
        if (file.is_open()) {
            string line;
            getline(file, line); // Skip header
            while (getline(file, line)) {
                stringstream ss(line);
                string id_str, name, specialization;
                getline(ss, id_str, ',');
                getline(ss, name, ',');
                getline(ss, specialization, ',');
                int id = stoi(id_str);
                addDoctor(id, name, specialization);
            }
            file.close();
            cout << "Doctors data loaded from " << fileName << "." << endl;
        } else {
            cout << "No existing doctors data file found. Starting with empty list." << endl;
        }
    }
};

//Appointments Linked List
class AppointmentsLL{
private:
    AppointmentNode* head;

public:
    AppointmentsLL() : head(nullptr){}

    AppointmentNode* finAppointment(int appointment_id) { //find appointment by id
        AppointmentNode* current = head;
        while (current) {
            if (current->appointment_id ==  appointment_id)
                return current;
            current = current->next;
        }
        return nullptr;
    }
    void addAppointment( int appointment_id, int doctor_id, int patient_id, string appointment_date){ //add a new appointment
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

    void displayAppointments(){ //display all appointments
        AppointmentNode* node = head;
        while (node != nullptr){
            cout<<"Appointment ID: "<<node->appointment_id<<",  Patient ID: "<<node->patient_id<<",  Doctor ID: "<<node->doctor_id<<",  Date: "<<node->appointment_date<<endl;
            node = node->next;
        }
    }

    void saveToCSV(const string& fileName) { //save all appointments to a csv file
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

    void loadFromCSV(const string& fileName) { //load appointments from csv file
        ifstream file(fileName);
        if (file.is_open()) {
            string line;
            getline(file, line); // Skip header
            while (getline(file, line)) {
                stringstream ss(line);
                string id_str, patient_id_str, doctor_id_str, date;
                getline(ss, id_str, ',');
                getline(ss, patient_id_str, ',');
                getline(ss, doctor_id_str, ',');
                getline(ss, date, ',');
                int id = stoi(id_str);
                int patient_id = stoi(patient_id_str);
                int doctor_id = stoi(doctor_id_str);
                addAppointment(id, doctor_id, patient_id, date);
            }
            file.close();
            cout << "Appointments data loaded from " << fileName << "." << endl;
        } else {
            cout << "No existing appointments data file found. Starting with empty list." << endl;
        }
    }
};

void display_menu(){// menu
    cout<<"Menu: \n";
    cout<<"1. Register a patient\n";
    cout<<"2. Register a doctor \n";
    cout<<"3. Register an appointment\n";
    cout<<"4. Display Patients\n";
    cout<<"5. Display Doctors\n";
    cout<<"6. Display Appointments\n";
    cout<<"7. Exit\n\n";
}

void display_welcome(){ //welcome message
    cout<<" _______________________________________________________________________"<<endl;
    cout<<"|                                                                       |"<<endl;
    cout<<"|         RUHENGERI REFERRAL HOSPITAL | APPOINTMENTS SYSTEM             |"<<endl;
    cout<<"|                                                                       |"<<endl;
    cout<<"| _____________________________________________________________________ |\n\n"<<endl;
}

void check_number_input(int &num){ //check if the input is a number
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

bool validate_date(string& date) { //validate date in (YYYY/MM/DD) format
    regex date_pattern(R"(\d{4}/\d{2}/\d{2})");
    return regex_match(date, date_pattern);
}

string getValidDate(const string& prompt) { //get valid date 
    string date;
    do {
        cout << prompt;
        getline(cin, date);
        if (!validate_date(date)) {
            cout << "Invalid date format. Please use YYYY/MM/DD." << endl;
        }
    } while (!validate_date(date));
    return date;
}

int main() {
    display_welcome();
    PatientsLL patientsLinkedList;
    DoctorsLL doctorsLinkedList;
    AppointmentsLL appointmentsLinkedlist;

    // Load existing data
    patientsLinkedList.loadFromCSV(PATIENTS_FILE);
    doctorsLinkedList.loadFromCSV(DOCTORS_FILE);
    appointmentsLinkedlist.loadFromCSV(APPOINTMENTS_FILE);

    while (true){
        display_menu();
        int choice;
        cout << "Enter your choice: ";
        cin>>choice;

        check_number_input(choice);

        switch(choice) { //switch case to go throught all the menus
            case 1: { //add patient
                int id;
                string name, dob, gender;
                cout << "ID: ";
                cin >> id;
                check_number_input(id);

                PatientNode *patient_exists = patientsLinkedList.findPatient(id);
                while (patient_exists != nullptr) {
                    cout << "A patient with ID " << id << " already exists. Please choose a different ID." << endl;
                    cin>>id;
                    patient_exists = patientsLinkedList.findPatient(id);
                }

                cin.ignore(1, '\n');
                cout << "Name: ";
                getline(cin, name);
                dob = getValidDate("DOB (YYYY/MM/DD): ");
                cout << "Gender: ";
                getline(cin, gender);
                patientsLinkedList.addPatient(id, name, dob, gender);
                break;
            }
            case 2: { //add a doctor
                int id;
                string name, specialization;
                cout << "ID: ";
                cin >> id;
                check_number_input(id);

                DoctorNode *doctor_exists = doctorsLinkedList.findDoctor(id);
                while (doctor_exists != nullptr) {
                    cout << "A doctor with ID " << id << " already exists. Please choose a different ID." << endl;
                    cin>>id;
                    doctor_exists = doctorsLinkedList.findDoctor(id);
                }

                cin.ignore(1, '\n');
                cout << "Name: ";
                getline(cin, name);
                cout << "Specialization: ";
                getline(cin, specialization);
                doctorsLinkedList.addDoctor(id, name, specialization);
                break;
            }
            case 3: { // add an appointment
                int id, patient_id, doctor_id;
                string date;
                cout << "ID: ";
                cin >> id;
                check_number_input(id);

                AppointmentNode *appointment_exists = appointmentsLinkedlist.finAppointment(id);
                while (appointment_exists == nullptr) {
                    cout << "An appointment with ID " << id << " already exists. Please choose a different ID." << endl;
                    cin>>id;
                    appointment_exists = appointmentsLinkedlist.finAppointment(id);
                }

                cout << "P_ID: ";
                cin >> patient_id;
                check_number_input(patient_id);
                cout << "D_ID: ";
                cin >> doctor_id;
                check_number_input(doctor_id);
                cin.ignore(1, '\n');
                cout << "DATE: ";
                getline(cin, date);

                PatientNode* patient_exists = patientsLinkedList.findPatient(patient_id);
                DoctorNode* doctor_exists = doctorsLinkedList.findDoctor(doctor_id);

                if (patient_exists == nullptr) {
                    cerr << "[FAILED] Patient ID does not exist" << endl;
                    continue;
                }
                if (doctor_exists == nullptr) {
                    cerr << "[FAILED] Doctor ID does not exist" << endl;
                    continue;
                }

                appointmentsLinkedlist.addAppointment(id, doctor_id, patient_id, date);
                break;
            }
            case 4: // display patients
                patientsLinkedList.displayPatients();
                break;
            case 5: // display doctors
                doctorsLinkedList.displayDoctors();
                break;
            case 6: //display appoinemtns
                appointmentsLinkedlist.displayAppointments();
                break;
            case 7: // EXIT: save to csv file before exiting
                cout << "Saving information to .csv files" << endl;
                patientsLinkedList.saveToCSV(PATIENTS_FILE);
                doctorsLinkedList.saveToCSV(DOCTORS_FILE);
                appointmentsLinkedlist.saveToCSV(APPOINTMENTS_FILE);
                return 0;
            default: //invalid input
                cout << "Invalid input choice" << endl;
                break;
        }
    }
}
