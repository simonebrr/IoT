#ifndef TASK_H
#define TASK_H

class Task {
 public:
  virtual ~Task();
  virtual void init() = 0;
  virtual void execute() = 0;
  virtual unsigned int long getInterval() = 0;
};

#endif