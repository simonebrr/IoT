#ifndef TASK_H
#define TASK_H

class Task {
 protected:
  unsigned long lastExec;
  unsigned long interval;
  bool en;

 public:
  Task(unsigned long inteval);
  virtual ~Task() = default;

  virtual void init() = 0;
  virtual void execute() = 0;

  void run();
  void setEn(bool en) { this->en = en; }
  bool isEn() { return this->en; }
  void setInterval(unsigned long ms) { this->interval = ms; }
  unsigned long getInterval() { return this->interval; }
};

#endif