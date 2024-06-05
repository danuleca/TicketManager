#include <iostream>
#include <cstring>
#include <ctime>

using namespace std;

enum Country {BULGARIA, SERBIA, HUNGARY, ITALY, SPAIN, SWEDEN};
enum City {SOFIA, BELGRADE, BUDAPEST, ROME, MADRID, STOCKHOLM, SUNNYBEACH, PIROT, MILAN};

Country inputCountry(const char* countryName)
{
    if(strcmp(countryName, "Bulgaria") == 0) return BULGARIA;
    if(strcmp(countryName, "Serbia") == 0) return SERBIA;
    if(strcmp(countryName, "Hungary") == 0) return HUNGARY;
    if(strcmp(countryName, "Italy") == 0) return ITALY;
    if(strcmp(countryName, "Spain") == 0) return SPAIN;
    if(strcmp(countryName, "Sweden") == 0) return SWEDEN;
    else throw invalid_argument("Invalid country!");
}

City inputCity(const char* cityName)
{
    if(strcmp(cityName, "Sofia") == 0) return SOFIA;
    if(strcmp(cityName, "Belgrade") == 0) return BELGRADE;
    if(strcmp(cityName, "Budapest") == 0) return BUDAPEST;
    if(strcmp(cityName, "Rome") == 0) return ROME;
    if(strcmp(cityName, "Madrid") == 0) return MADRID;
    if(strcmp(cityName, "Stockholm") == 0) return STOCKHOLM;
    if(strcmp(cityName, "SunnyBeach") == 0) return SUNNYBEACH;
    if(strcmp(cityName, "Pirot") == 0) return PIROT;
    if(strcmp(cityName, "Milan") == 0) return MILAN;
    else throw invalid_argument("Invalid city!");
}

char* outputCountry(Country countryOfOrigin)
{
    char* countryName = new char[20];
    switch(countryOfOrigin)
    {
        case BULGARIA: strcpy(countryName, "Bulgaria"); break;
        case SERBIA: strcpy(countryName, "Serbia"); break;
        case HUNGARY: strcpy(countryName, "Hungary"); break;
        case ITALY: strcpy(countryName, "Italy"); break;
        case SPAIN: strcpy(countryName, "Spain"); break;
        case SWEDEN: strcpy(countryName, "Sweden"); break;
    }
    return countryName;
}

char* outputCity(City city)
{
    char* cityName = new char[20];
    switch(city)
    {
        case SOFIA: strcpy(cityName, "Sofia"); break;
        case BELGRADE: strcpy(cityName, "Belgrade"); break;
        case BUDAPEST: strcpy(cityName, "Budapest"); break;
        case ROME: strcpy(cityName, "Rome"); break;
        case MADRID: strcpy(cityName, "Madrid"); break;
        case STOCKHOLM: strcpy(cityName, "Stockholm"); break;
        case SUNNYBEACH: strcpy(cityName, "SunnyBeach"); break;
        case PIROT: strcpy(cityName, "Pirot"); break;
        case MILAN: strcpy(cityName, "Milan"); break;
    }
    return cityName;
}

const char * dupCStr(const char *str){
    int len = strlen(str);
    char *result = new char[len + 1];
    for(int i = 0; i<len; i++){
        result[i] = str[i];
    }
    return result;
}

bool isVehicleNumberValid(const char* vehicleNumber){
    int letterCount = 0;
    int digitCount = 0;
    int len = strlen(vehicleNumber);
    if (len <= 0 || len > 5) return false;
    for (int i = 0; i < len; i++) {
        if ((vehicleNumber[i] >= 'a' && vehicleNumber[i] <= 'z') || (vehicleNumber[i] >= 'A' && vehicleNumber[i] <= 'Z')) letterCount++;
        if (vehicleNumber[i] >= '0' && vehicleNumber[i] <= '9')  digitCount++;
    }
    if(letterCount >= 1 && digitCount >= 2) return true;
    else return false;
}

bool isValidName(const char* name){
    int len = strlen(name);
    if (len <= 0 || len > 20) return false;
    if(name[0] < 'A' || name[0] > 'Z') return false;
    for (int i = 1; i < len; i++) {
        if ((name[i] >= 'a' && name[i] <= 'z')) continue;
        return false;
    }
    return true;
}

const int secondsFor7Days = 604800;

class Ticket{
    private:
        const char* ticketNumber;
        float price;
        time_t date;
        const char* vehicleNumber;
        Country countryOfOrigin;
        char* firstName;
        char* lastName;
        bool active;
        unsigned int id;
        static size_t numberOfTickets;

        const char * dupCStr(const char *str){
        int len = strlen(str);
        char *result = new char[len + 1];
        for(int i = 0; i<len; i++){
            result[i] = str[i];
        }
        return result;
    }

    public:

        Ticket()
        : ticketNumber(const_cast<char*>("12asd")), price(0), date(time(NULL)), vehicleNumber(const_cast<char*>("45gh")), countryOfOrigin(BULGARIA), firstName(const_cast<char*>("Ivan")), lastName(const_cast<char*>("Ivanov")), active(true)
        {
            numberOfTickets++;
            id = numberOfTickets;
        }

        Ticket(const char* ticketNumber, const float price, const time_t date, const char* vehicleNumber, const Country countryOfOrigin, const char* firstName, const char* lastName)
        : ticketNumber(dupCStr(ticketNumber)), price(price), date(date), vehicleNumber(dupCStr(vehicleNumber)), countryOfOrigin(countryOfOrigin), firstName(strdup(firstName)), lastName(strdup(lastName)),  active(true)
        {
            if(id < 0) throw invalid_argument("Id cannot be negative!");
            if(price < 0) throw invalid_argument("Price cannot be negative!");
            if(ticketNumber == nullptr || vehicleNumber == nullptr || firstName == nullptr || lastName == nullptr) throw invalid_argument("Nullptr!");
            if(date < time(0)+secondsFor7Days) throw invalid_argument("Date cannot be past!");
            if(!isVehicleNumberValid(vehicleNumber)) throw invalid_argument("Invalid vehicle number!");
            if(countryOfOrigin < 0 || countryOfOrigin > 5) throw invalid_argument("Invalid country of origin!");
            if(!isValidName(firstName)) throw invalid_argument("Invalid first name!");
            if(!isValidName(lastName)) throw invalid_argument("Invalid last name!");

            numberOfTickets++;
            id = numberOfTickets;
        }
        
        Ticket(const Ticket& other)
        : ticketNumber(dupCStr(other.ticketNumber)), price(other.price), date(other.date), vehicleNumber(dupCStr(other.vehicleNumber)), countryOfOrigin(other.countryOfOrigin), firstName(strdup(other.firstName)), lastName(strdup(other.lastName)), active(true)
        {
            numberOfTickets++;
            id = numberOfTickets;
        }

        virtual void printTicketInfo()
        {
            cout << "ID: " << id << endl;
            cout << "Ticket number: " << ticketNumber << endl;
            cout << "Price: " << price << endl;
            cout << "Date: " << date << endl;
            cout << "Vehicle number: " << vehicleNumber << endl;
            cout << "Country of origin: " << outputCountry(countryOfOrigin) << endl;
            cout << "First name: " << firstName << endl;
            cout << "Last name: " << lastName << endl;
            cout << "Active: " << active << endl;
        }

        virtual const char* getTicketType() const = 0;

        virtual void updateTicket(
            const char* ticketNumber, 
            const float price, 
            const time_t date, 
            const char* vehicleNumber, 
            const Country countryOfOrigin, 
            const char* firstName, 
            const char* lastName, 
            const bool active
        ) = 0;

        void cancelTrip()
        {
                if(active == true)
                {
                    active = false;
                    cout << "Trip cancelled!" << endl;
                }
                else throw invalid_argument("Trip is already cancelled!");
        }

        ~Ticket()
        {
            if (ticketNumber != nullptr) delete[] ticketNumber;
            if (vehicleNumber != nullptr) delete[] vehicleNumber;
            if (firstName != nullptr) delete[] firstName;
            if (lastName != nullptr) delete[] lastName;
            numberOfTickets--;
        }

        //Setters
        void setTicketNumber(const char* ticketNumber)
        {
            if(ticketNumber == nullptr) throw invalid_argument("Nullptr!");
            this->ticketNumber = dupCStr(ticketNumber);
        }
        void setPrice(const float price)
        {
            if(price < 0) throw invalid_argument("Price cannot be negative!");
            this->price = price;
        }
        void setDate(const time_t date)
        {
            if(date < time(0)+secondsFor7Days) throw invalid_argument("Date cannot be past!");
            this->date = date;
        }
        void setVehicleNumber(const char* vehicleNumber)
        {
            if(vehicleNumber == nullptr) throw invalid_argument("Nullptr!");
            if(!isVehicleNumberValid(vehicleNumber)) throw invalid_argument("Invalid vehicle number!");
            this->vehicleNumber = dupCStr(vehicleNumber);
        }
        void setCountryOfOrigin(const Country countryOfOrigin)
        {
            if(countryOfOrigin < 0 || countryOfOrigin > 5) throw invalid_argument("Invalid country of origin!");
            this->countryOfOrigin = countryOfOrigin;
        }
        void setFirstName(const char* firstName)
        {
            if(firstName == nullptr) throw invalid_argument("Nullptr!");
            if(!isValidName(firstName)) throw invalid_argument("Invalid first name!");
            this->firstName = strdup(firstName);
        }
        void setLastName(const char* lastName)
        {
            if(lastName == nullptr) throw invalid_argument("Nullptr!");
            if(!isValidName(lastName)) throw invalid_argument("Invalid last name!");
            this->lastName = strdup(lastName);
        }
        void setActive(const bool active)
        {
            this->active = active;
        }

        //Getters
        int getId() const
        {
            return id;
        }
        const char* getTicketNumber() const
        {
            return ticketNumber;
        }
        float getPrice() const
        {
            return price;
        }
        time_t getDate() const
        {
            return date;
        }
        const char* getVehicleNumber() const
        {
            return vehicleNumber;
        }
        Country getCountryOfOrigin() const
        {
            return countryOfOrigin;
        }
        char* getFirstName() const
        {
            return firstName;
        }
        char* getLastName() const
        {
            return lastName;
        }
        bool getActive() const
        {
            return active;
        }
        static size_t getNumberOfTickets()
        {
            return numberOfTickets;
        }
};

size_t Ticket::numberOfTickets = 0;

class FlightTicket : public Ticket
{
    private:
        Country destinationCountry;
        char* travelingClass;

    public:
        FlightTicket()
         : Ticket(), destinationCountry(BULGARIA), travelingClass(strdup("Business"))
        {
        }

        FlightTicket(const char* ticketNumber, const float price, const time_t date, const char* vehicleNumber, const Country countryOfOrigin, const char* firstName, const char* lastName, const Country destinationCountry, const char* travelingClass)
        : Ticket(ticketNumber, price, date, vehicleNumber, countryOfOrigin, firstName, lastName), destinationCountry(destinationCountry), travelingClass(strdup(travelingClass))
        {
            if(destinationCountry < 0 || destinationCountry > 5) throw invalid_argument("Invalid destination country!");
            if(travelingClass == nullptr) throw invalid_argument("Nullptr!");
            if(strcmp(travelingClass, "Business") != 0 && strcmp(travelingClass, "Economy") != 0 && strcmp(travelingClass, "FirstClass") != 0) throw invalid_argument("Invalid traveling class!");
        }

        FlightTicket(const FlightTicket& other)
        : Ticket(other), destinationCountry(other.destinationCountry), travelingClass(strdup(other.travelingClass))
        {
        }

        FlightTicket &operator=(const FlightTicket& other)
        {
            if(this != &other)
            {
                setTicketNumber(other.getTicketNumber());
                setPrice(other.getPrice());
                setDate(other.getDate());
                setCountryOfOrigin(other.getCountryOfOrigin());
                setFirstName(other.getFirstName());
                setLastName(other.getLastName());
                destinationCountry = other.destinationCountry;
                travelingClass = strdup(other.travelingClass);
            }
            return *this;
        }
        
        
        void printTicketInfo()
        {
            Ticket::printTicketInfo();
            cout << "Destination country: " << outputCountry(destinationCountry) << endl;
            cout << "Traveling class: " << travelingClass << endl;
        }

        //Getters
        Country getDestinationCountry() const
        {
            return destinationCountry;
        }
        const char* getTravelingClass() const
        {
            return travelingClass;
        }
        const char* getTicketType() const
        {
            return "FlightTicket";
        }

        //Setters
        void setDestinationCountry(const Country destinationCountry)
        {
            if(destinationCountry < 0 || destinationCountry > 5) throw invalid_argument("Invalid destination country!");
            this->destinationCountry = destinationCountry;
        }
        void setTravelingClass(const char* travelingClass)
        {
            if(travelingClass == nullptr) throw invalid_argument("Nullptr!");
            if(strcmp(travelingClass, "Business") != 0 && strcmp(travelingClass, "Economy") != 0 && strcmp(travelingClass, "FirstClass") != 0) throw invalid_argument("Invalid traveling class!");
            travelingClass = strdup(travelingClass);
        }


        void updateTicket(
            const char* ticketNumber, 
            const float price, 
            const time_t date, 
            const char* vehicleNumber, 
            const Country countryOfOrigin, 
            const char* firstName, 
            const char* lastName, 
            const bool active
        ) override
        {
            setTicketNumber(ticketNumber);
            setPrice(price);
            setDate(date);
            setVehicleNumber(vehicleNumber);
            setCountryOfOrigin(countryOfOrigin);
            setFirstName(firstName);
            setLastName(lastName);
        }

        void updateTicket(
            const char* ticketNumber, 
            const float price, 
            const time_t date, 
            const char* vehicleNumber, 
            const Country countryOfOrigin, 
            const char* firstName, 
            const char* lastName, 
            const bool active,
            const Country destinationCountry,
            const char* travelingClass
        )
        {
            updateTicket(ticketNumber, price, date, vehicleNumber, countryOfOrigin, firstName, lastName, true);
            setDestinationCountry(destinationCountry);
            setTravelingClass(travelingClass);
        }
};

class TrainTicket : public Ticket
{
    private:
        City from;
        City to;
        char* travelingClass;
    
    public:
        TrainTicket()
         : Ticket(), from(SOFIA), to(MILAN), travelingClass(strdup("Bussiness"))
        {
        }

        TrainTicket(const char* ticketNumber, const float price, const time_t date, const char* vehicleNumber, const Country countryOfOrigin, const char* firstName, const char* lastName, const City from, const City to, const char* travelingClass)
        : Ticket(ticketNumber, price, date, vehicleNumber, countryOfOrigin, firstName, lastName), from(from), to(to), travelingClass(strdup(travelingClass))
        {
            if(from < 0 || from > 9) throw invalid_argument("Invalid from city!");
            if(to < 0 || to > 9) throw invalid_argument("Invalid to city!");
            if(travelingClass == nullptr) throw invalid_argument("Nullptr!");
            if(strcmp(travelingClass, "FirstClass") != 0 && strcmp(travelingClass, "SecondClass") != 0 && strcmp(travelingClass, "SleepWagon") != 0) throw invalid_argument("Invalid traveling class!");
        }

        TrainTicket(const TrainTicket& other)
        : Ticket(other), from(other.from), to(other.to), travelingClass(strdup(other.travelingClass))
        {
        }

        TrainTicket &operator=(const TrainTicket& other)
        {
            if(this != &other)
            {
                setTicketNumber(other.getTicketNumber());
                setPrice(other.getPrice());
                setDate(other.getDate());
                setCountryOfOrigin(other.getCountryOfOrigin());
                setFirstName(other.getFirstName());
                setLastName(other.getLastName());
                from = other.from;
                to = other.to;
                travelingClass = strdup(other.travelingClass);
            }
            return *this;
        }

        ~TrainTicket()
        {
            delete[] travelingClass;
        }

        void printTicketInfo()
        {
            Ticket::printTicketInfo();
            cout << "From: " << outputCity(from) << endl;
            cout << "To: " << outputCity(to) << endl;
            cout << "Traveling class: " << travelingClass << endl;
        }

        //Getters
        City getFrom() const
        {
            return from;
        }
        City getTo() const
        {
            return to;
        }
        const char* getTravelingClass() const
        {
            return travelingClass;
        }
        const char* getTicketType() const
        {
            return "TrainTicket";
        }

        //Setters
        void setFrom(const City from)
        {
            if(from < 0 || from > 9) throw invalid_argument("Invalid from city!");
            this->from = from;
        }
        void setTo(const City to)
        {
            if(to < 0 || to > 9) throw invalid_argument("Invalid to city!");
            this->to = to;
        }
        void setTravelingClass(const char* travelingClass)
        {
            if(travelingClass == nullptr) throw invalid_argument("Nullptr!");
            if(strcmp(travelingClass, "FirstClass") != 0 && strcmp(travelingClass, "SecondClass") != 0 && strcmp(travelingClass, "SleepWagon") != 0) throw invalid_argument("Invalid traveling class!");
            travelingClass = strdup(travelingClass);
        }

        void updateTicket(
            const char* ticketNumber, 
            const float price, 
            const time_t date, 
            const char* vehicleNumber, 
            const Country countryOfOrigin, 
            const char* firstName, 
            const char* lastName, 
            const bool active
        ) override
        {
            setTicketNumber(ticketNumber);
            setPrice(price);
            setDate(date);
            setVehicleNumber(vehicleNumber);
            setCountryOfOrigin(countryOfOrigin);
            setFirstName(firstName);
            setLastName(lastName);
        }

        void updateTicket(const char* ticketNumber, const float price, const time_t date, const char* vehicleNumber, const Country countryOfOrigin, const char* firstName, const char* lastName, const City from, const City to, const char* travelingClass) 
        {
            updateTicket(ticketNumber, price, date, vehicleNumber, countryOfOrigin, firstName, lastName, true);
            setFrom(from);
            setTo(to);
            setTravelingClass(travelingClass);
        }
};

class BusTicket : public Ticket
{
    private:
        City from;
        City to;
    
    public:
        BusTicket()
         : Ticket(), from(SOFIA), to(MILAN)
        {
        }
        
        BusTicket(const char* ticketNumber, const float price, const time_t date, const char* vehicleNumber, const Country countryOfOrigin, const char* firstName, const char* lastName, const City from, const City to)
        : Ticket(ticketNumber, price, date, vehicleNumber, countryOfOrigin, firstName, lastName), from(from), to(to)
        {
            if(from < 0 || from > 9) throw invalid_argument("Invalid from city!");
            if(to < 0 || to > 9) throw invalid_argument("Invalid to city!");
        }

        BusTicket(const BusTicket& other)
        : Ticket(other), from(other.from), to(other.to)
        {
        }

        BusTicket &operator=(const BusTicket& other)
        {
            if(this != &other)
            {
                setTicketNumber(other.getTicketNumber());
                setPrice(other.getPrice());
                setDate(other.getDate());
                setCountryOfOrigin(other.getCountryOfOrigin());
                setFirstName(other.getFirstName());
                setLastName(other.getLastName());
                from = other.from;
                to = other.to;
            }
            return *this;
        }
        
        ~BusTicket()
        {
        }
        
        void printTicketInfo()
        {
            Ticket::printTicketInfo();
            cout << "From: " << outputCity(from) << endl;
            cout << "To: " << outputCity(to) << endl;
        }
        //Getters
        City getFrom() const
        {
            return from;
        }
        City getTo() const
        {
            return to;
        }
        const char* getTicketType() const
        {
            return "BusTicket";
        }
        
        //Setters
        void setFrom(const City from)
        {
            if(from < 0 || from > 9) throw invalid_argument("Invalid from city!");
            this->from = from;
        }
        void setTo(const City to)
        {
            if(to < 0 || to > 9) throw invalid_argument("Invalid to city!");
            this->to = to;
        }

        void updateTicket(
            const char* ticketNumber, 
            const float price, 
            const time_t date, 
            const char* vehicleNumber, 
            const Country countryOfOrigin, 
            const char* firstName, 
            const char* lastName, 
            const bool active
        ) override
        {
            setTicketNumber(ticketNumber);
            setPrice(price);
            setDate(date);
            setVehicleNumber(vehicleNumber);
            setCountryOfOrigin(countryOfOrigin);
            setFirstName(firstName);
            setLastName(lastName);
        }


        void updateTicket(const char* ticketNumber, const float price, const time_t date, const char* vehicleNumber, const Country countryOfOrigin, const char* firstName, const char* lastName, const City from, const City to) 
        {
            updateTicket(ticketNumber, price, date, vehicleNumber, countryOfOrigin, firstName, lastName, true);
            setFrom(from);
            setTo(to);
        }

};

class Tourist
{
    private:
        char* firstName;
        char* lastName;
        Ticket** tripHistory;
        float amount;
        size_t size = 0;
        size_t capacity = 2;

    public:

        Tourist(const char* firstName, const char* lastName, const float amount)
        : firstName(strdup(firstName)), lastName(strdup(lastName)), amount(amount), size(0), capacity(2)
        {
            if(firstName == nullptr || lastName == nullptr) throw invalid_argument("Nullptr!");
            if(!isValidName(firstName)) throw invalid_argument("Invalid first name!");
            if(!isValidName(lastName)) throw invalid_argument("Invalid last name!");
            if(amount < 0) throw invalid_argument("Amount cannot be negative!");
            tripHistory = new Ticket*[capacity];
        }

        Tourist(const Tourist& other)
        : firstName(other.firstName), lastName(other.lastName), amount(other.amount), size(other.size), capacity(other.capacity)
        {
        }

        void resize()
        {
            capacity *= 2;
            Ticket** newTripHistory = new Ticket*[capacity];
            for (int i = 0; i < size; i++)
            {
                newTripHistory[i] = tripHistory[i];
            }
            delete[] tripHistory;
            tripHistory = newTripHistory;
        }

        Tourist &operator=(const Tourist& other)
        {
            if(this != &other)
            {
                if (firstName != nullptr) delete[] firstName;
                if (lastName != nullptr) delete[] lastName;
                firstName = strdup(other.firstName);
                lastName = strdup(other.lastName);
                amount = other.amount;
                size = other.size;
                capacity = other.capacity;
                delete[] tripHistory;
                tripHistory = other.tripHistory;
            }
            return *this;
        }

        ~Tourist()
        {
            delete[] firstName;
            delete[] lastName;
            for (int i = 0; i < size; i++)
            {
                delete tripHistory[i];
            }
            delete[] tripHistory;
        }

        //Getters
        char* getFirstName() const
        {
            return firstName;
        }
        char* getLastName() const
        {
            return lastName;
        }
        float getAmount() const
        {
            return amount;
        }
        Ticket** getHistory() const
        {
            return tripHistory;
        }  
        size_t getSize() const
        {
            return size;
        }
        size_t getCapacity() const
        {
            return capacity;
        }

        //Setters
        void setFirstName(const char* firstName)
        {
            if(firstName == nullptr) throw invalid_argument("Nullptr!");
            if(!isValidName(firstName)) throw invalid_argument("Invalid first name!");
            this->firstName = strdup(firstName);
        }
        void setLastName(const char* lastName)
        {
            if(lastName == nullptr) throw invalid_argument("Nullptr!");
            if(!isValidName(lastName)) throw invalid_argument("Invalid last name!");
            this->lastName = strdup(lastName);
        }
        void setAmount(const float amount)
        {
            if(amount < 0) throw invalid_argument("Amount cannot be negative!");
            this->amount = amount;
        }



        void useTheTrain(TrainTicket& ticket)
        {
            if(size >= capacity) resize();
            if(ticket.getPrice()>amount) throw invalid_argument("Not enough money!");
            amount -= ticket.getPrice();
            tripHistory[size] = &ticket;
            size++;
        }
        void useTheBus(BusTicket& ticket)
        {
            if(size >= capacity) resize();
            if(ticket.getPrice()>amount) throw invalid_argument("Not enough money!");
            amount -= ticket.getPrice();
            tripHistory[size] = &ticket;
            size++;
        }
        void bookAFlight(FlightTicket& ticket)
        {
            if(size >= capacity) resize();
            if(ticket.getPrice()>amount) throw invalid_argument("Not enough money!");
            amount -= ticket.getPrice();
            tripHistory[size] = &ticket;
            size++;
        }

        void printTripHistory()
        {
            for (int i = 0; i < size; i++)
            {
                tripHistory[i]->printTicketInfo();
            }
        }

        Ticket* findTicketById(const int id)
        {
            if(id < 0) throw invalid_argument("Invalid id!");
            for(int i=0; i < size; i++)
            {
                if(tripHistory[i]->getId() == id) return tripHistory[i];
            }
            throw invalid_argument("Invalid id!");
        }

        const char* findTicketTypeById(const int id)
        {
            if(id < 0) throw invalid_argument("Invalid id!");
            return findTicketById(id)->getTicketType();
        }

        void cancelTicketById(const int id)
        {
            if(id < 0) throw invalid_argument("Invalid id!");
            Ticket* ticket = findTicketById(id);
            ticket->cancelTrip();
        }

        void updateTicketById(const int id)
        {
            if(id < 0) throw invalid_argument("Invalid id!");
            Ticket* ticket = findTicketById(id);
            const char* type = findTicketTypeById(id);
            char ticketNumber[256]; 
            float price; 
            time_t date; 
            char vehicleNumber[256]; 
            Country countryOfOrigin;
            char countryOfOriginStr[256];
            if(strcmp(type, "FlightTicket") == 0)
            { 
                Country destination;
                char destinationStr[256];
                char travelingClass[256];
                try{
                    cout << "Enter ticket number: ";
                    cin >> ticketNumber;

                    cout << "Enter vehicle number: ";
                    cin >> vehicleNumber;

                    cout << "Enter price: ";
                    cin >> price;

                    cout << "Enter date: ";
                    cin >> date;

                    cout << "Enter country of origin(one of Bulgaria, Serbia, Hungary, Italy, Spain, Sweden): ";
                    cin >> countryOfOriginStr;
                    countryOfOrigin = inputCountry(countryOfOriginStr);

                    cout << "Enter destination(one of Bulgaria, Serbia, Hungary, Italy, Spain, Sweden): ";
                    cin >> destinationStr;
                    destination = inputCountry(destinationStr);

                    cout << "Enter traveling class(one of Economy, Business, First): ";
                    cin >> travelingClass;

                    FlightTicket* flightTicket = dynamic_cast<FlightTicket*>(ticket);
                    flightTicket->setTicketNumber(ticketNumber);
                    flightTicket->setVehicleNumber(vehicleNumber);
                    flightTicket->setPrice(price);
                    flightTicket->setDate(date);
                    flightTicket->setCountryOfOrigin(countryOfOrigin);
                    flightTicket->setDestinationCountry(destination);
                    flightTicket->setTravelingClass(travelingClass);
                }
                catch(const invalid_argument& e)
                {
                    cout << e.what() << endl;
                }
            }
            if(strcmp(type, "BusTicket") == 0)
            {
                City to;
                char toStr[256];
                City from;
                char fromStr[256];
                try{
                    cout << "Enter ticket number: ";
                    cin >> ticketNumber;

                    cout << "Enter vehicle number: ";
                    cin >> vehicleNumber;

                    cout << "Enter price: ";
                    cin >> price;

                    cout << "Enter date: ";
                    cin >> date;

                    cout << "Enter country of origin(one of Bulgaria, Serbia, Hungary, Italy, Spain, Sweden): ";
                    cin >> countryOfOriginStr;
                    countryOfOrigin = inputCountry(countryOfOriginStr);

                    cout << "Enter from city(one of Sofia, Belgrade, Budapest, Rome, Madrid, Stockholm, SunnyBeach, Pirot, Milan): ";
                    cin >> fromStr;
                    from = inputCity(fromStr);

                    cout << "Enter to city(one of Sofia, Belgrade, Budapest, Rome, Madrid, Stockholm, SunnyBeach, Pirot, Milan): ";
                    cin >> toStr;
                    to = inputCity(toStr);

                    BusTicket* busTicket = dynamic_cast<BusTicket*>(ticket);
                    busTicket->setTicketNumber(ticketNumber);
                    busTicket->setVehicleNumber(vehicleNumber);
                    busTicket->setPrice(price);
                    busTicket->setDate(date);
                    busTicket->setCountryOfOrigin(countryOfOrigin);
                    busTicket->setFrom(from);
                    busTicket->setTo(to);
                }
                catch(const invalid_argument& e)
                {
                    cout << e.what() << endl;
                }
            }
            if(strcmp(type, "TrainTicket") == 0)
            {
                City to;
                char toStr[256];
                City from;
                char fromStr[256];
                char travelClass[256];
                try{
                    cout << "Enter ticket number: ";
                    cin >> ticketNumber;

                    cout << "Enter vehicle number: ";
                    cin >> vehicleNumber;

                    cout << "Enter price: ";
                    cin >> price;

                    cout << "Enter date: ";
                    cin >> date;

                    cout << "Enter country of origin(one of Bulgaria, Serbia, Hungary, Italy, Spain, Sweden): ";
                    cin >> countryOfOriginStr;
                    countryOfOrigin = inputCountry(countryOfOriginStr);

                    cout << "Enter from city(one of Sofia, Belgrade, Budapest, Rome, Madrid, Stockholm, SunnyBeach, Pirot, Milan): ";
                    cin >> fromStr;
                    from = inputCity(fromStr);

                    cout << "Enter to city(one of Sofia, Belgrade, Budapest, Rome, Madrid, Stockholm, SunnyBeach, Pirot, Milan): ";
                    cin >> toStr;
                    to = inputCity(toStr);

                    cout << "Enter traveling class(one of FirstClass, SecondClass, SleepWagon): ";
                    cin >> travelClass;

                    TrainTicket* trainTicket = dynamic_cast<TrainTicket*>(ticket);
                    trainTicket->setTicketNumber(ticketNumber);
                    trainTicket->setVehicleNumber(vehicleNumber);
                    trainTicket->setPrice(price);
                    trainTicket->setDate(date);
                    trainTicket->setCountryOfOrigin(countryOfOrigin);
                    trainTicket->setFrom(from);
                    trainTicket->setTo(to);
                    trainTicket->setTravelingClass(travelClass);
                }
                catch(const invalid_argument& e)
                {
                    cout << e.what() << endl;
                }
            }
            
        } 
};

int main()
{
    char firstName[256];
    char lastName[256];
    float amount;

    while (true) {
        try {
            cout << "Enter first name: ";
            cin >> firstName;
            cout << "Enter last name: ";
            cin >> lastName;
            cout << "Enter amount: ";
            cin >> amount;
            Tourist tourist(firstName, lastName, amount);
            break;
        }
        catch (const invalid_argument& e) {
            cout << e.what() << " Please try again." << endl;
            cin.clear();
        }
    }
    Tourist tourist(firstName, lastName, amount);

    int choice = 0;
    while (true) {
        cout << "Please choose one of the following:" << endl;
        cout << "1. Use Plane" << endl;
        cout << "2. Use Bus" << endl;
        cout << "3. Use Train" << endl;
        cout << "4. List tickets history" << endl;
        cout << "5. Update ticket by ID" << endl;
        cout << "6. Cancel ticket by ID" << endl;
        cout << "7. Quit" << endl;
        cout << "Enter your choice (1-7): ";
        cin >> choice;
        cout << endl;

        char ticketNumber[256];
        char vehicleNumber[256];
        float price;
        time_t date;
        Country countryOfOrigin;
        char countryOfOriginStr[256];
        Country destination;
        char destinationStr[256];
        char travelClass[256];
        City from;
        char fromStr[256];
        City to;
        char toStr[256];
        int id;

        switch (choice) {
            case 1:
            {
                try{
                    cout << "Enter ticket number: ";
                    cin >> ticketNumber;

                    cout << "Enter vehicle number: ";
                    cin >> vehicleNumber;

                    cout << "Enter price: ";
                    cin >> price;

                    cout << "Enter date: ";
                    cin >> date;

                    cout << "Enter country of origin(one of Bulgaria, Serbia, Hungary, Italy, Spain, Sweden): ";
                    cin >> countryOfOriginStr;
                    countryOfOrigin = inputCountry(countryOfOriginStr);

                    cout << "Enter destination(one of Bulgaria, Serbia, Hungary, Italy, Spain, Sweden): ";
                    cin >> destinationStr;
                    destination = inputCountry(destinationStr);

                    cout << "Enter traveling class(one of Business, Economy, FirstClass): ";
                    cin >> travelClass;

                    FlightTicket *f1 = new FlightTicket(ticketNumber, price, date, vehicleNumber, countryOfOrigin, firstName, lastName, destination, travelClass);
                    tourist.bookAFlight(*f1);
                }
                catch (const invalid_argument& e) {
                    cout << e.what() << " Please try again." << endl;
                    cin.clear();
                }
                cout << "Booked a flight!" << endl;
                break;
            }
            case 2:
            {
                try{
                    cout << "Enter ticket number: ";
                    cin >> ticketNumber;

                    cout << "Enter vehicle number: ";
                    cin >> vehicleNumber;

                    cout << "Enter price: ";
                    cin >> price;

                    cout << "Enter date: ";
                    cin >> date;

                    cout << "Enter country of origin(one of Bulgaria, Serbia, Hungary, Italy, Spain, Sweden): ";
                    cin >> countryOfOriginStr;
                    countryOfOrigin = inputCountry(countryOfOriginStr);

                    cout << "Enter from city(one of Sofia, Belgrade, Budapest, Rome, Madrid, Stockholm, SunnyBeach, Pirot, Milan): ";
                    cin >> fromStr;
                    from = inputCity(fromStr);

                    cout << "Enter to city(one of Sofia, Belgrade, Budapest, Rome, Madrid, Stockholm, SunnyBeach, Pirot, Milan): ";
                    cin >> toStr;
                    to = inputCity(toStr);

                    BusTicket *b1 = new BusTicket(ticketNumber, price, date, vehicleNumber, countryOfOrigin, firstName, lastName, from, to);
                    tourist.useTheBus(*b1);
                }
                catch (const invalid_argument& e) {
                    cout << e.what() << " Please try again." << endl;
                    cin.clear();
                }
                cout << "Used the bus!" << endl;
                break;
            }
            case 3:
            {
                try{
                    cout << "Enter ticket number: ";
                    cin >> ticketNumber;

                    cout << "Enter vehicle number: ";
                    cin >> vehicleNumber;

                    cout << "Enter price: ";
                    cin >> price;

                    cout << "Enter date: ";
                    cin >> date;

                    cout << "Enter country of origin(one of Bulgaria, Serbia, Hungary, Italy, Spain, Sweden): ";
                    cin >> countryOfOriginStr;
                    countryOfOrigin = inputCountry(countryOfOriginStr);

                    cout << "Enter from city(one of Sofia, Belgrade, Budapest, Rome, Madrid, Stockholm, SunnyBeach, Pirot, Milan): ";
                    cin >> fromStr;
                    from = inputCity(fromStr);

                    cout << "Enter to city(one of Sofia, Belgrade, Budapest, Rome, Madrid, Stockholm, SunnyBeach, Pirot, Milan): ";
                    cin >> toStr;
                    to = inputCity(toStr);

                    cout << "Enter traveling class(one of FirstClass, SecondClass, SleepWagon): ";
                    cin >> travelClass;

                    TrainTicket *t1 = new TrainTicket(ticketNumber, price, date, vehicleNumber, countryOfOrigin, firstName, lastName, from, to, travelClass);
                    tourist.useTheTrain(*t1);
                }
                catch (const invalid_argument& e) {
                    cout << e.what() << " Please try again." << endl;
                    cin.clear();
                }
                break;
            }
            case 4:
            {
                tourist.printTripHistory();
                break;
            }
            case 5:
            {
                try{
                    cout << "Enter ticket ID: ";
                    cin >> id;
                    tourist.updateTicketById(id);
                }
                catch (const invalid_argument& e) {
                    cout << e.what() << " Please try again." << endl;
                    cin.clear();
                }
                break;
            }
            case 6:
                try{
                    cout << "Enter ticket ID: ";
                    cin >> id;
                    tourist.cancelTicketById(id);
                }
                catch (const invalid_argument& e) {
                    cout << e.what() << " Please try again." << endl;
                    cin.clear();
                }
                break;
            case 7:
            {
                cout << "Quitting..." << endl;
                return 0;
            }
            default:
            {
                cout << "Invalid choice. Please try again." << endl;
                break;
            }
        }
    }
}