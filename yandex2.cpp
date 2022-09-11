#include <iostream>
#include <list>
#include <vector>
using namespace std;

class VersionVisitor;
class FunctionListVisitor;

class Device {
public:
	virtual void accept(VersionVisitor*)=0;
	virtual void accept(FunctionListVisitor*)=0;
	virtual ~Device() {
	}
};

class SmartSocket: public Device {
	bool on;
	int id;
public:
	SmartSocket() {
		this->on = true;
		this->id = 13;
	}
	void turnOn() {
		this->on = true;
	}
	void turnOff() {
		this->on = false;
	}
	void toggle() {
		this->on = !this->on;
	}
	void accept(VersionVisitor *version_visitor) {
		cout << "Smart socket v." << this->id << endl;
	}
	void accept(FunctionListVisitor *visitor) {
		cout << "turnOn()" << endl;
		cout << "turnOff()" << endl;
		cout << "toggle()" << endl;
	}
};

class SmartLight: public Device {
	size_t light;
	double id;
public:
	SmartLight() {
		this->light = 0;
		this->id = 3.11;
	}
	void off() {
		this->light = 0;
	}
	void on(size_t light = 50) {
		this->light = light % 101;
	}
	void increase(size_t d = 1) {
		this->light += d;
		this->light %= 101;
	}
	void decrease(size_t d = 1) {
		if (this->light <= d)
			this->light = 0;
		else
			this->light -= d;
	}
	void accept(VersionVisitor *version_visitor) {
		cout << "Smart light v." << this->id << endl;
	}
	void accept(FunctionListVisitor *visitor) {
		cout << "on()" << endl;
		cout << "off()" << endl;
		cout << "increase()" << endl;
		cout << "decrease()" << endl;
	}
};

class FireAlarmSystem: public Device {
	bool alarm;
	string id;
public:
	FireAlarmSystem() {
		this->alarm = false;
		this->id = "11f";
	}
	void on() {
		this->alarm = true;
	}
	void off() {
		this->alarm = false;
	}
	void accept(VersionVisitor *version_visitor) {
		cout << "Fire alarm system v." << this->id << endl;
	}
	void accept(FunctionListVisitor *visitor) {
		cout << "on()" << endl;
		cout << "off()" << endl;
	}
};

class SecurityAlarmSystem: public Device {
	bool alarm;
	string id;
public:
	SecurityAlarmSystem() {
		this->alarm = false;
		this->id = "1-12s";
	}
	void on() {
		this->alarm = true;
	}
	void off() {
		this->alarm = false;
	}
	void accept(VersionVisitor *version_visitor) {
		cout << "Security alarm system v." << this->id << endl;
	}
	void accept(FunctionListVisitor *visitor) {
		cout << "on()" << endl;
		cout << "off()" << endl;
	}
};

class CoffeeMachine: public Device {
	size_t regime;
	double id;
	enum regimes {
		OFF, LATTE, CAPPUCINO, ESPRESSO, RISTRETTO
	};
public:
	CoffeeMachine() {
		this->regime = OFF;
		this->id = 5.55;
	}

	void setRegime(size_t regime) {
		this->regime = regime % 5;
	}

	void off() {
		this->regime = OFF;
	}

	void makeCoffee() {
		switch (this->regime) {
		case OFF:
			cout << "Machine is off!" << endl;
			return;
		case LATTE:
			cout << "Making latte..." << endl << "\t Done!" << endl;
			return;
		case CAPPUCINO:
			cout << "Making cappucino..." << endl << "\t Done!" << endl;
			return;
		case ESPRESSO:
			cout << "Making espresso..." << endl << "\t Done!" << endl;
			return;
		case RISTRETTO:
			cout << "Making ristretto..." << endl << "\t Done!" << endl;
			return;
		}
	}
	void accept(VersionVisitor *version_visitor) {
		cout << "Coffee machine v." << this->id << endl;
	}
	void accept(FunctionListVisitor *visitor) {
		cout << "setRegime(size_t)" << endl;
		cout << "off()" << endl;
		cout << "makeCoffee()" << endl;
	}
};

class MusicCenter: public Device {
	string song;
	bool on;
	string id;
public:
	MusicCenter() {
		this->on = false;
		this->id = "2.5.2-thunderball";
		this->song = "";
	}
	void setSong(string song) {
		this->song = song;
	}
	void turnOn() {
		this->on = true;
	}
	void turnOff() {
		this->on = false;
	}
	void play() {
		if (!this->on) {
			cout << "Music center is off!" << endl;
			return;
		} else if (this->song == "") {
			cout << "No song selected!" << endl;
			return;
		} else {
			cout << "Playing " << this->song << endl;
			return;
		}
	}
	void accept(VersionVisitor *version_visitor) {
		cout << "Music center v." << this->id << endl;
	}
	void accept(FunctionListVisitor *visitor) {
		cout << "setSong(string)" << endl;
		cout << "turnOn()" << endl;
		cout << "turnOff()" << endl;
		cout << "play()" << endl;
	}
};

class ControlDevice;

class AbstractCommand {
public:
	virtual void execute()=0;
	virtual string name()=0;
	virtual ~AbstractCommand() {
	}
};

class AbstractObserver {
public:
	virtual void update(vector<AbstractCommand*> soft)=0;
	virtual ~AbstractObserver() {
	}
};

class SocketCommand;
class LightCommand;
class FireAlarmCommand;
class SecurityAlarmCommand;
class CoffeeMachineCommand;
class MusicCenterCommand;
class ControlCommand;

class AbstractSubject {
public:
	virtual void attach(AbstractObserver*)=0;
	virtual void detach(AbstractObserver*)=0;
	virtual void notify()=0;
	virtual void addCommand(SocketCommand*)=0;
	virtual void addCommand(LightCommand*)=0;
	virtual void addCommand(FireAlarmCommand*)=0;
	virtual void addCommand(SecurityAlarmCommand*)=0;
	virtual void addCommand(CoffeeMachineCommand*)=0;
	virtual void addCommand(MusicCenterCommand*)=0;
	virtual void addCommand(ControlCommand*)=0;
	virtual void addCommand(AbstractCommand*)=0;
	virtual ~AbstractSubject() {
	}
};

class User: public AbstractObserver {
	AbstractSubject *subject;
	int id;
	vector<AbstractCommand*> soft;
	vector<size_t> strategy;
public:
	User(AbstractSubject *subject) {
		this->id = rand();
		this->subject = subject;
		cout << "User " << this->id << " joins YandexPlus" << endl;
		this->subject->attach(this);
	}

	int getId() {
		return this->id;
	}

	void update(vector<AbstractCommand*> soft) {
		cout << "User " << this->id << " receives software updates" << endl;
		this->soft.clear();
		for (AbstractCommand *command : soft) {
			cout << "Adding command: " << command->name() << "..." << endl;
			this->soft.push_back(command);
		}
	}

	void listSoft() {
		cout << "User " << this->id << " has the following commands available:"
				<< endl;
		int i = 0;
		for (AbstractCommand *command : this->soft) {
			cout << i << ": " << command->name() << endl;
			i++;
		}
	}

	void run(size_t i) {
		if (i >= this->soft.size()) {
			cout << "Command #" << i << " does not exist!" << endl;
			return;
		}
		this->soft[i]->execute();
	}

	void printStrategy() {
		cout << "Current strategy: " << endl;
		for (auto i : this->strategy)
			cout << this->soft[i]->name() << endl;
	}

	void runStrategy() {
		for (auto i : this->strategy)
			this->run(i);
	}

	void makeStrategy() {
		while (true) {
			size_t c;
			this->listSoft();
			cout << endl;
			this->printStrategy();
			cout << endl
					<< "Enter the number of the command you want to add to your strategy"
					<< endl << "0 to stop making the strategy and execute it"
					<< endl;
			cin >> c;
			if (c == 0) {
				this->runStrategy();
				return;
			}
			if (c >= this->soft.size()) {
				cout << "Command #" << c << " does not exist!" << endl;
				continue;
			}
			this->strategy.push_back(c);

		}
	}

	~User() {
		cout << "User " << this->id << " leaves YandexPlus";
		this->subject->detach(this);
	}
};

class SocketCommand: public AbstractCommand {
protected:
	SmartSocket *smart_socket;
public:
	SocketCommand(SmartSocket *smart_socket) {
		this->smart_socket = smart_socket;
	}
	void set(SmartSocket *smart_socket) {
		this->smart_socket = smart_socket;
	}
	virtual string name()=0;
	virtual void execute()=0;
};

class SocketOn: public SocketCommand {
public:
	SocketOn(SmartSocket *smart_socket = nullptr) :
			SocketCommand(smart_socket) {
	}
	string name() {
		return "Turn Smart Socket on";
	}
	void execute() {
		this->smart_socket->turnOn();
	}
};

class SocketOff: public SocketCommand {
public:
	SocketOff(SmartSocket *smart_socket = nullptr) :
			SocketCommand(smart_socket) {
	}
	string name() {
		return "Turn Smart Socket off";
	}
	void execute() {
		this->smart_socket->turnOff();
	}
};

class LightCommand: public AbstractCommand {
protected:
	SmartLight *smart_light;
public:
	LightCommand(SmartLight *smart_light) {
		this->smart_light = smart_light;
	}
	void set(SmartLight *smart_light) {
		this->smart_light = smart_light;
	}
	virtual string name()=0;
	virtual void execute()=0;
};

class LightOn: public LightCommand {
public:
	LightOn(SmartLight *smart_light = nullptr) :
			LightCommand(smart_light) {
	}
	string name() {
		return "Turn Smart Light on";
	}
	void execute() {
		this->smart_light->on();
	}
};

class LightOff: public LightCommand {
public:
	LightOff(SmartLight *smart_light = nullptr) :
			LightCommand(smart_light) {
	}
	string name() {
		return "Turn Smart Light off";
	}
	void execute() {
		this->smart_light->off();
	}
};

class LightIncrease: public LightCommand {
	int by;
public:
	LightIncrease(int by, SmartLight *smart_light = nullptr) :
			LightCommand(smart_light) {
		this->by = by;
	}
	string name() {
		return "Increase light by " + to_string(this->by);
	}
	void execute() {
		this->smart_light->increase(by);
	}
};

class LightDecrease: public LightCommand {
	int by;
public:
	LightDecrease(int by, SmartLight *smart_light = nullptr) :
			LightCommand(smart_light) {
		this->by = by;
	}
	string name() {
		return "Decrease light by " + to_string(this->by);
	}
	void execute() {
		this->smart_light->decrease(by);
	}
};

class FireAlarmCommand: public AbstractCommand {
protected:
	FireAlarmSystem *alarm;
public:
	FireAlarmCommand(FireAlarmSystem *alarm) {
		this->alarm = alarm;
	}
	void set(FireAlarmSystem *alarm) {
		this->alarm = alarm;
	}
	virtual string name()=0;
	virtual void execute()=0;
};

class FireAlarmOn: public FireAlarmCommand {
public:
	FireAlarmOn(FireAlarmSystem *alarm = nullptr) :
			FireAlarmCommand(alarm) {
	}
	string name() {
		return "Set fire alarm on";
	}
	void execute() {
		this->alarm->on();
	}
};

class FireAlarmOff: public FireAlarmCommand {
public:
	FireAlarmOff(FireAlarmSystem *alarm = nullptr) :
			FireAlarmCommand(alarm) {
	}
	string name() {
		return "Set fire alarm off";
	}
	void execute() {
		this->alarm->off();
	}
};

class SecurityAlarmCommand: public AbstractCommand {
protected:
	SecurityAlarmSystem *alarm;
public:
	SecurityAlarmCommand(SecurityAlarmSystem *alarm) {
		this->alarm = alarm;
	}
	void set(SecurityAlarmSystem *alarm) {
		this->alarm = alarm;
	}
	virtual string name()=0;
	virtual void execute()=0;
};

class SecurityAlarmOn: public SecurityAlarmCommand {
public:
	SecurityAlarmOn(SecurityAlarmSystem *alarm = nullptr) :
			SecurityAlarmCommand(alarm) {
	}
	string name() {
		return "Set security alarm on";
	}
	void execute() {
		this->alarm->on();
	}
};

class SecurityAlarmOff: public SecurityAlarmCommand {
public:
	SecurityAlarmOff(SecurityAlarmSystem *alarm = nullptr) :
			SecurityAlarmCommand(alarm) {
	}
	string name() {
		return "Set security alarm off";
	}
	void execute() {
		this->alarm->off();
	}
};

class CoffeeMachineCommand: public AbstractCommand {
protected:
	CoffeeMachine *coffee_machine;
	enum regimes {
		OFF, LATTE, CAPPUCINO, ESPRESSO, RISTRETTO
	};
public:
	CoffeeMachineCommand(CoffeeMachine *coffee_machine) {
		this->coffee_machine = coffee_machine;
	}
	void set(CoffeeMachine *coffee_machine) {
		this->coffee_machine = coffee_machine;
	}
	virtual void execute()=0;
	virtual string name()=0;
	virtual ~CoffeeMachineCommand() {
	}
};

class CoffeeMachineOff: public CoffeeMachineCommand {
public:
	CoffeeMachineOff(CoffeeMachine *coffee_machine = nullptr) :
			CoffeeMachineCommand(coffee_machine) {
	}
	string name() {
		return "Turn the coffee machine off";
	}
	void execute() {
		this->coffee_machine->setRegime(OFF);
	}
};

class CoffeeMachineMakeLatte: public CoffeeMachineCommand {
public:
	CoffeeMachineMakeLatte(CoffeeMachine *coffee_machine = nullptr) :
			CoffeeMachineCommand(coffee_machine) {
	}
	string name() {
		return "Make Latte in the coffee machine";
	}
	void execute() {
		this->coffee_machine->setRegime(LATTE);
		this->coffee_machine->makeCoffee();
	}
};

class CoffeeMachineMakeCappucino: public CoffeeMachineCommand {
public:
	CoffeeMachineMakeCappucino(CoffeeMachine *coffee_machine = nullptr) :
			CoffeeMachineCommand(coffee_machine) {
	}
	string name() {
		return "Make Cappucino in the coffee machine";
	}
	void execute() {
		this->coffee_machine->setRegime(CAPPUCINO);
		this->coffee_machine->makeCoffee();
	}
};

class CoffeeMachineMakeEspresso: public CoffeeMachineCommand {
public:
	CoffeeMachineMakeEspresso(CoffeeMachine *coffee_machine = nullptr) :
			CoffeeMachineCommand(coffee_machine) {
	}
	string name() {
		return "Make Espresso in the coffee machine";
	}
	void execute() {
		this->coffee_machine->setRegime(ESPRESSO);
		this->coffee_machine->makeCoffee();
	}
};

class CoffeeMachineMakeRistretto: public CoffeeMachineCommand {
public:
	CoffeeMachineMakeRistretto(CoffeeMachine *coffee_machine = nullptr) :
			CoffeeMachineCommand(coffee_machine) {
	}
	string name() {
		return "Make Ristretto in the coffee machine";
	}
	void execute() {
		this->coffee_machine->setRegime(RISTRETTO);
		this->coffee_machine->makeCoffee();
	}
};

class MusicCenterCommand: public AbstractCommand {
protected:
	MusicCenter *music_center;
public:
	MusicCenterCommand(MusicCenter *music_center) {
		this->music_center = music_center;
	}
	void set(MusicCenter *music_center) {
		this->music_center = music_center;
	}
	virtual string name()=0;
	virtual void execute()=0;
};

class MusicCenterOn: public MusicCenterCommand {
public:
	MusicCenterOn(MusicCenter *music_center = nullptr) :
			MusicCenterCommand(music_center) {
	}
	string name() {
		return "Turn music center on";
	}
	void execute() {
		this->music_center->turnOn();
	}
};

class MusicCenterOff: public MusicCenterCommand {
public:
	MusicCenterOff(MusicCenter *music_center = nullptr) :
			MusicCenterCommand(music_center) {
	}
	string name() {
		return "Turn music center off";
	}
	void execute() {
		this->music_center->turnOff();
	}
};

class MusicCenterPlaySong: public MusicCenterCommand {
public:
	string song_name;
	MusicCenterPlaySong(string song_name, MusicCenter *music_center = nullptr) :
			MusicCenterCommand(music_center) {
		this->song_name = song_name;
	}
	string name() {
		return "Play \"" + this->song_name + "\" with the Music center";
	}
	void execute() {
		this->music_center->setSong(song_name);
		this->music_center->play();
	}
};

class VersionVisitor {
	Device *device;

public:
	VersionVisitor() {
		this->device = nullptr;
	}
	void visit(Device *device) {
		this->device = device;
		this->device->accept(this);
	}
};

class FunctionListVisitor {
	Device *device;

public:
	FunctionListVisitor() {
		this->device = nullptr;
	}
	void visit(Device *device) {
		this->device = device;
		this->device->accept(this);
	}
};

class YandexPlus;
class ControlDevice: public Device {
	YandexPlus *controlled;
	VersionVisitor *version_visitor;
	FunctionListVisitor *function_visitor;
public:
	ControlDevice(YandexPlus *controlled) {
		this->controlled = controlled;
		this->version_visitor = new VersionVisitor;
		this->function_visitor = new FunctionListVisitor;
	}

	void printDevice(size_t);
	void listFunctions(size_t);
	void printDevices();

	void accept(VersionVisitor *visitor) {
	}
	void accept(FunctionListVisitor *visitor) {
	}
};

class ControlCommand: public AbstractCommand {
protected:
	ControlDevice *control_device;
public:
	virtual void execute()=0;
	virtual string name()=0;
	ControlCommand(ControlDevice *control_device = nullptr) {
		this->control_device = control_device;
	}
	void set(ControlDevice *control_device) {
		this->control_device = control_device;
	}
	virtual ~ControlCommand() {
	}
};

class YandexPlus: public AbstractSubject {
	list<AbstractObserver*> users;
	vector<Device*> devices;
	vector<AbstractCommand*> soft;
	enum devicenumbers {
		CONTROL, SOCKET, LIGHT, FIRE, SECURITY, COFFEE, MUSIC
	};

public:
	YandexPlus() {
		this->devices.push_back(new ControlDevice(this));
		this->devices.push_back(new SmartSocket);
		this->devices.push_back(new SmartLight);
		this->devices.push_back(new FireAlarmSystem);
		this->devices.push_back(new SecurityAlarmSystem);
		this->devices.push_back(new CoffeeMachine);
		this->devices.push_back(new MusicCenter);
	}

	void attach(AbstractObserver *observer) {
		this->users.push_back(observer);
	}

	void detach(AbstractObserver *observer) {
		users.remove(observer);
	}

	void addCommand(SocketCommand *command) {
		cout << "YandexPlus receives command:" << command->name() << endl;
		command->set((SmartSocket*) this->devices[SOCKET]);
		this->soft.push_back(command);
	}

	void addCommand(LightCommand *command) {
		cout << "YandexPlus receives command:" << command->name() << endl;
		command->set((SmartLight*) this->devices[LIGHT]);
		this->soft.push_back(command);
	}

	void addCommand(FireAlarmCommand *command) {
		cout << "YandexPlus receives command:" << command->name() << endl;
		command->set((FireAlarmSystem*) this->devices[FIRE]);
		this->soft.push_back(command);
	}

	void addCommand(SecurityAlarmCommand *command) {
		cout << "YandexPlus receives command:" << command->name() << endl;
		command->set((SecurityAlarmSystem*) this->devices[SECURITY]);
		this->soft.push_back(command);
	}

	void addCommand(CoffeeMachineCommand *command) {
		cout << "YandexPlus receives command:" << command->name() << endl;
		command->set((CoffeeMachine*) this->devices[COFFEE]);
		this->soft.push_back(command);
	}

	void addCommand(MusicCenterCommand *command) {
		cout << "YandexPlus receives command:" << command->name() << endl;
		command->set((MusicCenter*) this->devices[MUSIC]);
		this->soft.push_back(command);
	}

	void addCommand(ControlCommand *command) {
		command->set((ControlDevice*) this->devices[CONTROL]);
		this->soft.push_back(command);
	}

	void addCommand(AbstractCommand *command) {
		cout << "Error! This method should never get called" << endl;
	}

	void notify() {
		for (auto user : this->users) {
			user->update(this->soft);
		}
	}
	friend class ControlDevice;
};

void ControlDevice::printDevices() {
	for (auto device : this->controlled->devices) {
		this->version_visitor->visit(device);
	}
}

void ControlDevice::printDevice(size_t n) {
	this->version_visitor->visit(this->controlled->devices[n]);
}

void ControlDevice::listFunctions(size_t n) {
	this->function_visitor->visit(this->controlled->devices[n]);
}

class MakeStrategy: public ControlCommand {
public:
	void execute() {

	}
	string name() {
		return "Finish making strategy";
	}
};

int main() {
	AbstractSubject *y = new YandexPlus;

	y->addCommand(new MakeStrategy);
	y->addCommand(new SocketOn);
	y->addCommand(new SocketOff);
	y->addCommand(new LightOn);
	y->addCommand(new LightOff);
	y->addCommand(new LightIncrease(50));
	y->addCommand(new LightDecrease(50));
	y->addCommand(new FireAlarmOn);
	y->addCommand(new FireAlarmOff);
	y->addCommand(new SecurityAlarmOn);
	y->addCommand(new SecurityAlarmOff);
	y->addCommand(new CoffeeMachineMakeLatte);
	y->addCommand(new CoffeeMachineMakeCappucino);
	y->addCommand(new CoffeeMachineMakeEspresso);
	y->addCommand(new CoffeeMachineMakeRistretto);
	y->addCommand(new CoffeeMachineOff);
	y->addCommand(new MusicCenterOn);
	y->addCommand(new MusicCenterOff);
	y->addCommand(
			new MusicCenterPlaySong("Pink Floyd - Shine on you crazy diamond"));
	y->addCommand(new MusicCenterPlaySong("Jethro Tull - Roots to Branches"));
	y->addCommand(
			new MusicCenterPlaySong("Mumford and Sons - Little Lion Man"));

	User *user = new User(y);
	y->notify();

	user->makeStrategy();

	return 0;
}
