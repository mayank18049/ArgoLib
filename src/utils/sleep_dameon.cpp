#include <chrono>
#include "cpucounters.h" //PCM related: https://github.com/intel/pcm
#include "utils.h"       //PCM related: https://github.com/intel/pcm

#define millisleep(a) std::sleep_for(std::chrono::milliseconds(a))

namespace energy_daemon{
  
static PCM *___pcm;
static volatile bool shutdown = false;
const int fixed_interval = 100;
const int warmup_interval = 5;
static bool inital = true;

enum actions = {DEC, INC};
void init_pcm(){
  ___pcm->program();
  PCM::ErrorCode status = ___pcm->program();
  switch (status)
    {
    case PCM::Success:
        break;
    default:
        std::cerr << "Access to Processor Counter Monitor has denied (Unknown error)." << std::endl;
        exit(EXIT_FAILURE);
    }
  ___pcm = PCM::getInstance();
  ___pcm->resetPMU(); 
}

SystemCounterState returnCounterState(){
    return getSystemCounterState();
}
double returnJoules(SystemCounterState before, SystemCounterState after){
  return getConsumedJoules(before,after);
}
double returnInst(SystemCounterState before, SystemCounterState after){
  return getInstructionsRetired(before,after);
}
double returnJPI(SystemCounterState before, after){
  double consumed_joules = returnJoules(before,after);
  double retired_inst = returnInst(before,after);
  return retierd_inst/consumed_joules;
}

void configureDOP(double prev, double curr){
  static actions lastAction = INC;
  const int wChange=2; // find experimentally on your system
  if(inital) {
    sleep_argolib_num_workers(wChange);
    lastAction=DEC;
    return;
    }
    if(curr - prev < 0) {
      if(lastAction==DEC) {
        sleep_argolib_num_workers(wChange);
        } else {
          awake_argolib_num_workers(wChange);
        }
    } else{
      if(lastAction == DEC) {
        awake_argolib_num_workers(wChange);
        lastAction = INC;
      } else {
        sleep_argolib_num_workers(wChange);
        lastAction = DEC;
      }
    }
}


void pcm_cleanup(){
  ___pcm->cleanup();
}

void start_daemon(){
  init_pcm();
  
  SystemCounterState before, after;
  before = returnCounterState(); 
  millisleep(warmup_interval);
  double JPI_prev = 0;
  double JPI_curr = 0;
  while(!shutdown){
    after = retrunCounterState();
    JPI_curr = returnJPI(before,after);
    configure_DOP(JPI_prev, JPI_curr);
    before = after;
    JPI_prev = JPI_curr;
    sleep(fixed_interval);

  }

}
void stop_daemon(){
  shutdown = true;
}
}