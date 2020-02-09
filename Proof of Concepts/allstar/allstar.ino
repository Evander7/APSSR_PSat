// All Star with Buzzer Proof of Concept
// For APSSR PSat 2020
// Written by Amelia Cordwell

//first verse
// frequency (square wave)
int all_star_verse_1[][2] = {{370,600},{554,300},{466,300},{466,600},{415,300},{370,300},{370,300},{494,600},{466,300},{466,300} ,{415,300} ,
{415,300} ,{370,600} ,{370,300} ,{554,300} ,{466,300} ,{466,600} ,{415,300} ,{370,300} ,{370,300} ,{311,600} ,{277,900},{370,300} ,{370,300} ,{554,300},
{0, 500}};
int num_notes = sizeof(all_star_verse_1) / sizeof(all_star_verse_1[0]);


#define buzzer_pin 9 
#define buzzer_pin_2 10

int note_index = 0;
int interval = 0;
int current_millis = 0;
int previous_millis = 0;

bool buzzer_on = 0;


void setup(){
  start_buzzer();
}

void loop(){
   buzzer_loop();
}

void start_buzzer(){
  buzzer_on = 1;
  note_index = 0;

  previous_millis = millis();
  note_index++;
  if (note_index >= num_notes){
    note_index = 0;
  }
  tone(buzzer_pin, all_star_verse_1[0][0], all_star_verse_1[0][1]);
//  tone(buzzer_pin_2, all_star_verse_1[0][0], all_star_verse_1[0][1]);

}

void buzzer_loop(){
   if (buzzer_on == 0){
      return;
   }

   int current_millis = millis();
   if((current_millis - interval) > previous_millis) {
      previous_millis = millis();
      note_index++;
      if (note_index >= num_notes){
        note_index = 0;
      }
      interval = all_star_verse_1[note_index][1];
      tone(buzzer_pin, all_star_verse_1[note_index][0], interval);
//      tone(buzzer_pin_2, all_star_verse_1[note_index][0], interval);
      Serial.println("buzz");

   }

}

void end_buzzer(){
  buzzer_on = 0;
}
