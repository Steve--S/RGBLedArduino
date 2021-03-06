// A demonstration of multiple strings on a single controller.
//
// By Mike Tsao <http://github.com/sowbug>

#include <G35.h>
#include <LightProgram.h>
#include <ProgramRunner.h>
#include <StockPrograms.h>
#include <PlusPrograms.h>

// How long each program should run.
#define PROGRAM_DURATION_SECONDS (30)

#define LIGHT_COUNT (50)

#define USING_TEENSY_AS_LEONARDO (0)

#if USING_TEENSY_AS_LEONARDO
// A Teensy 2.0 that's been flashed with the Arduino Leonardo bootloader (thus
// permanently destroying the HalfKay bootloader that ships with the Teensy).
// The first string is connected to D6, and the second to B4. 
G35 lights_1(12, LIGHT_COUNT);
G35 lights_2(8, LIGHT_COUNT);
#else
// Standard Arduino, string 1 on Pin 13, string 2 on Pin 14.
G35 lights_1(13, LIGHT_COUNT);
G35 lights_2(14, LIGHT_COUNT);
#endif

// -1 because SteadyWhite is more of a mode than a program.
#define PROGRAM_COUNT (STOCK_PROGRAM_COUNT + PLUS_PROGRAM_COUNT - 1)
LightProgram* CreateProgram(G35& lights, uint8_t program_index) {
  switch (program_index) {
  case 0: return new Orbit(lights, true);
  case 1: return new Orbit(lights, false);
  case 2: return new CrossOverWave(lights);
  case 3: return new ForwardWave(lights);
  case 4: return new ChasingRainbow(lights);
  case 5: return new AlternateDirectionalWave(lights);
  case 6: return new FadeInFadeOutSolidColors(lights);
  case 7: return new BidirectionalWave(lights);
  case 8: return new ChasingSolidColors(lights);
  case 9: return new FadeInFadeOutMultiColors(lights);
  case 10: return new RandomSparkling(lights);
  case 11: return new ChasingMultiColors(lights);
  case 12: return new ChasingWhiteRedBlue(lights);
  case 13: return new Meteorite(lights);
  case 14: return new Twinkle(lights);
  case 15: return new RedGreenChase(lights);
  case 16: return new Pulse(lights);
  case 17: return new Cylon(lights);
  case 18: return new Stereo(lights);
  case PROGRAM_COUNT:
  default:
    // PROBLEM! PROGRAM_COUNT is wrong.
    return NULL;
  }
}

LightProgram* CreateProgram_1(uint8_t program_index) {
  return CreateProgram(lights_1, program_index);
}

LightProgram* CreateProgram_2(uint8_t program_index) {
  return CreateProgram(lights_2, program_index);
}

ProgramRunner runner_1(CreateProgram_1, PROGRAM_COUNT,
                       PROGRAM_DURATION_SECONDS);
ProgramRunner runner_2(CreateProgram_2, PROGRAM_COUNT,
                       PROGRAM_DURATION_SECONDS);

void setup() {
  randomSeed(analogRead(0));

  delay(50);
  lights_1.enumerate_forward();
  lights_2.enumerate_forward();
  delay(50);

  lights_1.test_patterns();
  lights_2.test_patterns();
}

void loop() {
  runner_1.loop();
  runner_2.loop();
}
