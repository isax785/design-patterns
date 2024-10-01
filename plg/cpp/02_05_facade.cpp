#include <iostream>

using namespace std;

// ========== Subsystem Classes ==========

struct DVDPlayer {
    void on() {cout << "DVD Player is ON" << endl;}
    void off() {cout << "DVD Player is OFF" << endl;}
    void play(const char* movie) {cout << "Playing '" << movie << "'" << endl;}
    void stop() {cout << "Stopping DVD player";}
};

struct Projector {
    void on() {cout << "Projector is ON" << endl;}
    void off() {cout << "Projector is OFF" << endl;}
    void wide_screen_mode() {cout << "Projector in Wide-Screen Mode" << endl;}    
};

struct SurroundSoundSystem {
    void on() {cout << "Surround Sound System is ON" << endl;}
    void off() {cout << "Surround Sound System is OFF" << endl;}
    void set_volume(int level) {cout << "Setting volume to " << level << endl;}    
};

struct Lights {
    void dim(float level) {cout << "Dimming lights to " << level << "%" << endl;}
};

struct PopcornPopper {
    void on() {cout << "Popcorn Popper is ON" << endl;}
    void off() {cout << "Popcorn Popper is OFF" << endl;}
    void pop() {cout << "Popping popcorn" << endl;}
};

// ========== Facade Class ==========

struct HomeTheaterFacade {
    Projector* _projector;
    DVDPlayer* _dvdplayer;
    SurroundSoundSystem* _soundsystem;
    Lights* _lights;
    PopcornPopper* _popper;
    HomeTheaterFacade(Projector* projector, DVDPlayer* dvdplayer, SurroundSoundSystem* soundsystem, Lights* lights,
    PopcornPopper* popper) : _projector(projector), _dvdplayer(dvdplayer), _soundsystem(soundsystem), _lights(lights), _popper(popper) {};
    void whatch_movie(const char* movie) {
        cout << "Get ready to watch a movie ..." << endl;
        _popper->on();
        _popper->pop();
        _lights->dim(10);
        _projector->on();
        _projector->wide_screen_mode();
        _soundsystem->on();
        _soundsystem->set_volume(5);
        _dvdplayer->on();
        _dvdplayer->play(movie);
        cout << "... enjoy!" << endl;
    }
    void end_movie() {
        cout << "Shutting down the home theater ..." << endl;
        _dvdplayer->stop();
        _dvdplayer->off();
        _soundsystem->off();
        _projector->off();
        _lights->dim(100);
        _popper->off();
        cout << "... done!" << endl;
    }
};

int main() {
    DVDPlayer* dvdplayer = new DVDPlayer();
    cout << "--- Testing DVDPlayer ---" << endl;
    const char* m = "Minions";
    dvdplayer->play(m);
    Projector* projector = new Projector();
    SurroundSoundSystem* soundsystem = new SurroundSoundSystem();
    Lights lights = Lights();
    PopcornPopper popper = PopcornPopper();
    HomeTheaterFacade htf = HomeTheaterFacade(projector, dvdplayer, soundsystem, &lights, &popper);
    htf.whatch_movie(m);
    htf.end_movie();
    return 0;
}