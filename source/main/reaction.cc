//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1993 - 2001 California Institute of Technology             //
//                                                                          //
// Read the COPYING and README files, or contact 'avida@alife.org',         //
// before continuing.  SOME RESTRICTIONS MAY APPLY TO USE OF THIS FILE.     //
//////////////////////////////////////////////////////////////////////////////

#ifndef REACTION_HH
#include "reaction.hh"
#endif

#ifndef REACTION_PROCESS_HH
#include "reaction_process.hh"
#endif
#ifndef REACTION_REQUISITE_HH
#include "reaction_requisite.hh"
#endif

using namespace std;

///////////////
//  cReaction
///////////////

cReaction::cReaction(const cString & _name, int _id)
  : name(_name)
  , id(_id)
  , task(NULL)
  , active(true)
{
}

cReaction::~cReaction()
{
  while (process_list.GetSize() != 0) delete process_list.Pop();
  while (requisite_list.GetSize() != 0) delete requisite_list.Pop();
}

cReactionProcess * cReaction::AddProcess()
{
  cReactionProcess * new_process = new cReactionProcess();
  process_list.PushRear(new_process);
  return new_process;
}

cReactionRequisite * cReaction::AddRequisite()
{
  cReactionRequisite * new_requisite = new cReactionRequisite();
  requisite_list.PushRear(new_requisite);
  return new_requisite;
}

bool cReaction::ModifyValue(double new_value, int process_num) {
  if (process_num >= process_list.GetSize() || process_num < 0) return false;
  process_list.GetPos(process_num)->SetValue(new_value);
  return true;
}
