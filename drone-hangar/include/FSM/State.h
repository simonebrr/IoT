#ifndef STATE_H
#define STATE_H

class State {
 public:
  virtual ~State() {}
  virtual void enter() = 0;
  virtual void execute() = 0;
  virtual void exit() = 0;
};

#endif