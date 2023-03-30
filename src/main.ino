#include <Control_Surface.h> // Include the Control Surface library

// Instantiate a MIDI over USB interface.
USBMIDI_Interface midi;

using namespace MIDI_Notes;

// Instantiate a NoteButton object
NoteButton button2 = {
  2,                       // Push button on pin 5
  {note(C, 4), CHANNEL_1}, // Note C4 on MIDI channel 1
};
NoteButton button3 = {
  3,                       // Push button on pin 5
  {note(D, 4), CHANNEL_1}, // Note C4 on MIDI channel 1
};
NoteButton button4 = {
  4,                       // Push button on pin 5
  {note(E, 4), CHANNEL_1}, // Note C4 on MIDI channel 1
};
NoteButton button5 = {
  5,                       // Push button on pin 5
  {note(F, 4), CHANNEL_1}, // Note C4 on MIDI channel 1
};
NoteButton button6 = {
  6,                       // Push button on pin 5
  {note(G, 4), CHANNEL_1}, // Note C4 on MIDI channel 1
};
NoteButton button7 = {
  7,                       // Push button on pin 5
  {note(A, 4), CHANNEL_1}, // Note C4 on MIDI channel 1
};
NoteButton button8 = {
  8,                       // Push button on pin 5
  {note(B, 4), CHANNEL_1}, // Note C4 on MIDI channel 1
};

void setup()
{
    button2.invert();
    button3.invert();
    button4.invert();
    button5.invert();
    button6.invert();
    button7.invert();
    button8.invert();
    Control_Surface.begin(); // Initialize Control Surface
}

void loop()
{
    Control_Surface.loop(); // Update the Control Surface
}
