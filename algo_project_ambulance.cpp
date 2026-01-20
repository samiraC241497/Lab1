#include <bits/stdc++.h>
using namespace std;

class Location {
public:
    string name;
    Location(string n) : name(n) {}
};

class Ambulance {
public:
    int id;
    string driver;
    int location;
    bool busy;
    Ambulance(int i, string d, int loc) : id(i), driver(d), location(loc), busy(false) {}
};

struct Emergency {
    string locName;
    int index;
    int priority;
    string type;
};


vector<Location> locations;
vector<Ambulance> ambulances;
vector<vector<double>> dist;

int getLocationIndex(const string &name){
    for(int i=0;i<locations.size();i++) if(locations[i].name==name) return i;
    return -1;
}

void addLocation(const string &name){locations.push_back(Location(name)); }

void addAmbulance(int id, string driver, string loc){
    int idx = getLocationIndex(loc);
    if(idx==-1) return;
    ambulances.push_back(Ambulance(id, driver, idx));
}

void floydWarshall(const vector<tuple<int,int,double>> &roads){
    int n = locations.size();
    dist.assign(n, vector<double>(n, 1e18));
    for(int i=0;i<n;i++) dist[i][i]=0;

    for(auto &[u,v,w]: roads){
        dist[u][v]=w;
        dist[v][u]=w;
    }

    for(int k=0;k<n;k++)
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                if(dist[i][k] < 1e18 && dist[k][j] < 1e18)
                    dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j]);
}

void printDistanceMatrix() {
    int n = dist.size();
    cout << endl<<"________________________________________________________________________________________________________________________"<<endl;
    cout << "                                      DISTANCE MATRIX (in kilometers)"<<endl;
    cout << "_______________________________________________________________________________________________________________________"<<endl<<endl;

    cout << "From \\ To        ";
    for (int j = 0; j < n; j++) {
        string loc = locations[j].name;
        if (loc.length() > 8) loc = loc.substr(0, 8);
        cout << setw(12) << loc;
    }
    cout <<endl<< string(15 + 12*n, '-') << endl;

    for (int i = 0; i < n; i++) {
        string from = locations[i].name;
        if (from.length() > 14) from = from.substr(0, 14);
        cout << left << setw(15) << from;

        for (int j = 0; j < n; j++) {
            if (dist[i][j] >= 1e17) {
                cout << setw(12) << "INF";
            } else if (i == j) {
                cout << setw(12) << "0";
            } else {
                cout << right << setw(10) << fixed << setprecision(1) << dist[i][j] << "  ";
            }
        }
        cout << endl;
    }
    cout << endl<<endl<<endl;
}

int assignNearestAmbulance(Emergency &e){
    double bestDist = 1e18;
    int bestAmb = -1;
    for(int i=0;i<ambulances.size();i++){
        if(ambulances[i].busy) continue;
        double d = dist[ambulances[i].location][e.index];
        if(d<bestDist){
            bestDist=d;
            bestAmb=i;
        }
    }
    return bestAmb;
}

void handleEmergenciesDC(vector<Emergency> &queue, int l, int r){
    if(l>r) return;
    if(l==r){
        Emergency e = queue[l];
        int amb = assignNearestAmbulance(e);
        if(amb==-1){
            cout<<"No free ambulance for emergency at "<<e.locName<<endl;
            return;
        }
        Ambulance &a = ambulances[amb];
        double distance = dist[a.location][e.index];
        a.busy = true;
        double time = distance/40*60;
        cout<<"=== Emergency Assigned ==="<<endl;
        cout<<"Location: "<<e.locName<<endl;
        cout<<"Accident Type: "<<e.type<<endl;
        cout<<"Ambulance ID: "<<a.id<<endl;
        cout<<"Driver: "<<a.driver<<endl;
        cout<<"From: "<<locations[a.location].name<<endl;
        cout<<"Distance: "<<fixed<<setprecision(1)<<distance<<" km"<<endl;
        cout<<"Estimated Arrival: "<<fixed<<setprecision(1)<<time<<" minutes"<<endl;
        a.location = e.index;
        return;
    }

    int mid = (l+r)/2;
    handleEmergenciesDC(queue,l,mid);
    handleEmergenciesDC(queue,mid+1,r);
}

void printAmbulances(){
    cout<<endl<<"=== Ambulances Status ==="<<endl<<endl;
    for(auto &a:ambulances){
        cout<<"ID: "<<a.id
            <<", Driver: "<<a.driver
            <<", Location: "<<locations[a.location].name
            <<", Status: "<<(a.busy?"BUSY":"FREE")<<endl;
    }
    cout<<endl;
}

void printMap(const vector<tuple<int,int,double>> &roads){
    cout<<"=== City Map ==="<<endl<<endl;
    for(auto &loc:locations){
        cout<<loc.name<<" -> ";
        bool first = true;
        for(auto &[u,v,w]:roads){
            if(u==getLocationIndex(loc.name)){
                if(!first) cout<<", ";
                cout<<locations[v].name<<"("<<w<<" km)";
                first = false;
            }
            else if(v==getLocationIndex(loc.name)){
                if(!first) cout<<", ";
                cout<<locations[u].name<<"("<<w<<" km)";
                first = false;
            }
        }
        cout<<endl<<endl;
    }
}

int main(){
    cout<<endl<<endl<<"                              === Intelligent Emergency Ambulance Dispatch System ==="<<endl;

    addLocation("Central Hospital");
    addLocation("North Hospital");
    addLocation("South Clinic");
    addLocation("East Medical Center");
    addLocation("West Emergency");
    addLocation("Downtown");
    addLocation("Residential Area");
    addLocation("Industrial Zone");

    vector<tuple<int,int,double>> roads;

    roads.push_back({getLocationIndex("Central Hospital"), getLocationIndex("Downtown"),5});
    roads.push_back({getLocationIndex("Central Hospital"), getLocationIndex("North Hospital"),8});
    roads.push_back({getLocationIndex("North Hospital"), getLocationIndex("Residential Area"),6});
    roads.push_back({getLocationIndex("South Clinic"), getLocationIndex("Downtown"),7});
    roads.push_back({getLocationIndex("South Clinic"), getLocationIndex("Industrial Zone"),4});
    roads.push_back({getLocationIndex("East Medical Center"), getLocationIndex("Residential Area"),5});
    roads.push_back({getLocationIndex("East Medical Center"), getLocationIndex("Industrial Zone"),6});
    roads.push_back({getLocationIndex("West Emergency"), getLocationIndex("Downtown"),9});
    roads.push_back({getLocationIndex("West Emergency"), getLocationIndex("Residential Area"),7});
    roads.push_back({getLocationIndex("Downtown"), getLocationIndex("Residential Area"),8});

    addAmbulance(101,"John Doe","Central Hospital");
    addAmbulance(102,"Jane Smith","North Hospital");
    addAmbulance(103,"Mike Johnson","South Clinic");
    addAmbulance(104,"Alice Brown","East Medical Center");
    addAmbulance(105,"Bob Davis","West Emergency");
    addAmbulance(106,"Carol Wilson","Downtown");

    floydWarshall(roads);

    printDistanceMatrix();

    printMap(roads);
    printAmbulances();

    int n;
    cout<<"How many emergency calls? ";
    cin>>n;
    cin.ignore();

    if(n <= 0){
        cout<<"No emergencies to process."<<endl;
        return 0;
    }

    vector<Emergency> emergencyQueue;
    for(int i=0;i<n;i++){
        Emergency e;
        cout<<"Enter emergency location: ";
        getline(cin, e.locName);
        e.index = getLocationIndex(e.locName);

        if(e.index == -1){
            cout<<"Invalid location! Please enter a valid location."<<endl;
            i--;
            continue;
        }

        cout<<"Enter accident type (Heart attack / Car accident / Minor injury / Checkup): ";
        getline(cin, e.type);

        if(e.type == "Heart attack") e.priority = 5;
        else if(e.type == "Car accident") e.priority = 4;
        else if(e.type == "Minor injury") e.priority = 3;
        else e.priority = 1;

        emergencyQueue.push_back(e);
    }

    // Sort by priority (highest first)
    sort(emergencyQueue.begin(), emergencyQueue.end(),
        [](Emergency &a, Emergency &b){ return a.priority > b.priority; });

    // Process all emergencies
    for(int i=0;i<emergencyQueue.size();i++){
        Emergency e = emergencyQueue[i];
        int amb = assignNearestAmbulance(e);
        if(amb==-1){
            cout<<"No free ambulance for emergency at "<<e.locName<<endl;
            continue;
        }
        Ambulance &a = ambulances[amb];
        double distance = dist[a.location][e.index];
        a.busy = true;
        double time = distance/40*60;
        cout<<"\n=== Emergency Assigned ==="<<endl;
        cout<<"Emergency #"<<(i+1)<<" (Priority: "<<e.priority<<")"<<endl;
        cout<<"Location: "<<e.locName<<endl;
        cout<<"Accident Type: "<<e.type<<endl;
        cout<<"Ambulance ID: "<<a.id<<endl;
        cout<<"Driver: "<<a.driver<<endl;
        cout<<"From: "<<locations[a.location].name<<endl;
        cout<<"Distance: "<<fixed<<setprecision(1)<<distance<<" km"<<endl;
        cout<<"Estimated Arrival: "<<fixed<<setprecision(1)<<time<<" minutes"<<endl;
        a.location = e.index;
    }

    printAmbulances();

    return 0;
}
