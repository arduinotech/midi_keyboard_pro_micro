#include <Control_Surface.h> // Include the Control Surface library
#include <Arduino.h>
// #include <Streaming.h>

USBMIDI_Interface midi;

using namespace MIDI_Notes;

int rowPinMap[8] = {6, 7, 8, 9, 10, 16, 14, 15};
int colPinMap[4] = {2, 3, 4, 5};

bool buttonsState[8][4] = {
    {false, false, false, false},
    {false, false, false, false},
    {false, false, false, false},
    {false, false, false, false},
    {false, false, false, false},
    {false, false, false, false},
    {false, false, false, false},
    {false, false, false, false}
};

int keysNum[8][4] = {
    {7, 15, 23, 31},
    {6, 14, 22, 30},
    {5, 13, 21, 29},
    {4, 12, 20, 28},
    {0, 8, 16, 24},
    {1, 9, 17, 25},
    {2, 10, 18, 26},
    {3, 11, 19, 27}
};

MIDIAddress keysAddress[32] = {
    {note(F, 2), CHANNEL_1}, {note(Gb, 2), CHANNEL_1}, {note(G, 2), CHANNEL_1}, {note(Ab, 2), CHANNEL_1},
    {note(A, 2), CHANNEL_1}, {note(Bb, 2), CHANNEL_1}, {note(B, 2), CHANNEL_1}, {note(C, 3), CHANNEL_1},
    {note(Db, 3), CHANNEL_1}, {note(D, 3), CHANNEL_1}, {note(Eb, 3), CHANNEL_1}, {note(E, 3), CHANNEL_1},
    {note(F, 3), CHANNEL_1}, {note(Gb, 3), CHANNEL_1}, {note(G, 3), CHANNEL_1}, {note(Ab, 3), CHANNEL_1},
    {note(A, 3), CHANNEL_1}, {note(Bb, 3), CHANNEL_1}, {note(B, 3), CHANNEL_1}, {note(C, 4), CHANNEL_1},
    {note(Db, 4), CHANNEL_1}, {note(D, 4), CHANNEL_1}, {note(Eb, 4), CHANNEL_1}, {note(E, 4), CHANNEL_1},
    {note(F, 4), CHANNEL_1}, {note(Gb, 4), CHANNEL_1}, {note(G, 4), CHANNEL_1}, {note(Ab, 4), CHANNEL_1},
    {note(A, 4), CHANNEL_1}, {note(Bb, 4), CHANNEL_1}, {note(B, 4), CHANNEL_1}, {note(C, 5), CHANNEL_1}
};

const uint8_t velocity = 0x7F;

void setup()
{
    // Serial.begin(115200);

    for (int row = 0; row < 8; row++)
        pinMode(rowPinMap[row], INPUT_PULLUP);

    for (int col = 0; col < 4; col++)
        pinMode(colPinMap[col], INPUT_PULLUP);

    Control_Surface.begin();
}

void loop()
{
    Control_Surface.loop(); // Update the Control Surface

    for (int row = 0; row < 8; row++) {
        int rowPin = rowPinMap[row];
        pinMode(rowPin, OUTPUT);
        digitalWrite(rowPin, LOW);
        for (int col = 0; col < 4; col++) {
            bool isKeyDown = !digitalRead(colPinMap[col]);
            if (isKeyDown) {
                if (!buttonsState[row][col]) {
                    buttonsState[row][col] = true;
                    midi.sendNoteOn(keysAddress[keysNum[row][col]], velocity);
                    // Serial << "button[" << row << "][" << col << "] - " << keysNum[row][col] << " - DOWN\n";
                }
            } else {
                if (buttonsState[row][col]) {
                    buttonsState[row][col] = false;
                    midi.sendNoteOff(keysAddress[keysNum[row][col]], velocity);
                    // Serial << "button[" << row << "][" << col << "] - " << keysNum[row][col] << " - UP\n";
                }
            }
        }
        digitalWrite(rowPin, HIGH);
        // delay(1);
        pinMode(rowPin, INPUT_PULLUP);
    }
}
