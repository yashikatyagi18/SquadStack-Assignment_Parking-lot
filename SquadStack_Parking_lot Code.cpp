#include <bits/stdc++.h>
#include <fstream>
#include <string>

using namespace std;
struct Car {
    string carNo;
    int ageOfDriver;
};
class ParkingLot{
public:
    vector<Car> slotInfo;
    int capacity;
    priority_queue<int, vector<int>, greater<int>> minSlotAvailable;
    unordered_map<string, int> slotNoByRc;
    ParkingLot(int slots){
        this->capacity = slots;
        for(int i=1;i<=slots;i++)
            minSlotAvailable.push(i);
        slotInfo.push_back({"", -1});
        for(int i=1;i<=slots;i++){
            slotInfo.push_back({"", -1});
        }
        cout<<"Created parking of "<<slots<<" slots"<<endl;
    }
    void slotNoByAge(int age){
       vector<int> slotAge;
        for(int i=1;i<=capacity;i++){
            if(slotInfo[i].ageOfDriver == age)
                slotAge.push_back(i);
        }
        if(slotAge.empty())
        cout<<"No car found with owner age"<<" "<<age;
         for(int i=1;i<=slotAge.size();i++){
             if(i==slotAge.size())
             cout<<slotAge[i-1];
             else
             cout<<slotAge[i-1]<<",";
         }
        cout<<endl;
        
    }
    void slotNoByCarRegNo(string carRC){
        if(slotNoByRc.count(carRC) == 0){
            cout<<"No Car Found\n";
        }
        else {
            cout<<slotNoByRc[carRC]<<endl;
        }
    }
    void parkCar(string carNo, int age){
        if(minSlotAvailable.size() == 0){
            cout<<"No Slots Available\n";
        }
        else{
            int x = minSlotAvailable.top();
            minSlotAvailable.pop();
            slotInfo[x].carNo = carNo;
            slotInfo[x].ageOfDriver = age;
            slotNoByRc[carNo] = x;
            cout<<"Car with vehicle registration number \""<<carNo<<"\" has been parked at slot number "<<x<<"\n";
        }
        
    }
    void removeCar(int slotNo){ 
        if(slotInfo[slotNo].ageOfDriver==-1){
            cout<<"Slot already vacant\n";
            return;
        }
        if(slotNo>capacity || slotNo<=0){
             cout<<"No such slot found"<<endl;
             return;
        }
        minSlotAvailable.push(slotNo);
        cout<<"Slot number " <<slotNo<<" vacated, the car with vehicle registration number \""
        <<slotInfo[slotNo].carNo<<"\" left the space, the driver of the car was of age "
        <<slotInfo[slotNo].ageOfDriver<<endl;
        slotNoByRc.erase(slotInfo[slotNo].carNo);
        slotInfo[slotNo].carNo = "";
        slotInfo[slotNo].ageOfDriver = -1;
    }
    void VehicleNoByAge(int age){
        vector<string> vehicleNoByAge;
        for(int i=1;i<=slotInfo.size();i++){
            if(slotInfo[i].ageOfDriver==age)
            vehicleNoByAge.push_back(slotInfo[i].carNo);
            
        }
        for(int i=1;i<=vehicleNoByAge.size();i++){
            if(i==vehicleNoByAge.size())
            cout<<vehicleNoByAge[i-1];
            else
            cout<<vehicleNoByAge[i-1]<<",";
        }
        cout<<endl;
    }
};

int main(){
    freopen("input.txt","r", stdin);
    string s;
    cin>>s;
    int slots;
    cin>>slots;
    string queryType;
    ParkingLot parkingLot(slots);
    while(cin>>queryType){
        if(queryType == "Park"){
            string carNo, a;
            cin>>carNo>>a;
            int age;
            cin>> age;
            parkingLot.parkCar(carNo, age);
        }
        else if(queryType == "Slot_numbers_for_driver_of_age"){
            int age;
            cin>>age;
            parkingLot.slotNoByAge(age);
        }
        else if(queryType == "Slot_number_for_car_with_number"){
            string carNo;
            cin>>carNo;
            parkingLot.slotNoByCarRegNo(carNo);
        }
        else if(queryType == "Leave"){
            int slot;
            cin>>slot;
            parkingLot.removeCar(slot);
        }
        else if(queryType=="Vehicle_registration_number_for_driver_of_age"){
            int age;
            cin>>age;
            parkingLot.VehicleNoByAge(age);
        }
    }
}
