//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1993 - 2003 California Institute of Technology             //
//                                                                          //
// Read the COPYING and README files, or contact 'avida@alife.org',         //
// before continuing.  SOME RESTRICTIONS MAY APPLY TO USE OF THIS FILE.     //
//////////////////////////////////////////////////////////////////////////////

#ifndef ANALYZE_GENOTYPE_HH
#define ANALYZE_GENOTYPE_HH

#include <fstream>

#ifndef FUNCTIONS_HH
#include "functions.hh"
#endif
#ifndef GENOME_HH
#include "genome.hh"
#endif
#ifndef STRING_HH
#include "string.hh"
#endif
#ifndef STRING_LIST_HH
#include "string_list.hh"
#endif
#ifndef STRING_UTIL_HH
#include "string_util.hh"
#endif
#ifndef TARRAY_HH
#include "tArray.hh"
#endif

// cAnalyzeGenotype    : Collection of information about loaded genotypes

class cGenome; // aggregate
class cInstSet;
class cString; // aggregate
template <class T> class tArray; // aggregate
class cStringList; // aggregate
class cStringUtil; // access

class cAnalyzeGenotype {
private:
  cGenome genome;            // Full Genome
  cInstSet & inst_set;       // Instruction set used in this genome
  cString name;              // Name, if one was provided in loading
  cString aligned_sequence;  // Sequence (in ASCII) after alignment
  cString tag;               // All genotypes in a batch can be tagged

  bool viable;

  // Group 1 : Load-in Stats (Only obtained if available for input file)
  int id_num;
  int parent_id;
  int parent2_id;
  int num_cpus;
  int total_cpus;
  int update_born;
  int update_dead;
  int depth;

  // Group 2 : Basic Execution Stats (Obtained from test CPUs)
  int length;
  int copy_length;
  int exe_length;
  double merit;
  int gest_time;
  double fitness;
  int errors;
  double div_type;

  tArray<int> task_counts;

  // Group 3 : Stats requiring parental genotype (Also from test CPUs)
  double fitness_ratio;
  double efficiency_ratio;
  double comp_merit_ratio;
  int parent_dist;
  int ancestor_dist;
  int lineage_label;
  cString parent_muts;

  // Group 4 : Landscape stats (obtained from testing all possible mutations)
  class cAnalyzeLandscape {
  public:
    double frac_dead;
    double frac_neg;
    double frac_neut;
    double frac_pos;
    cAnalyzeLandscape() : frac_dead(0.0), frac_neg(0.0),
			  frac_neut(0.0), frac_pos(0.0) { ; }
  };
  mutable cAnalyzeLandscape * landscape_stats;

  // Group 5 : More complex stats (obtained indvidually, through tests)
  cString task_order;

  cStringList special_args; // These are args placed after a ':' in details...

  int NumCompare(double new_val, double old_val) const {
    if (new_val == old_val) return  0;
    else if (new_val == 0)       return -2;
    else if (old_val == 0)       return +2;
    else if (new_val < old_val)  return -1;
    // else if (new_val > old_val)
    return +1;
  }

  int CalcMaxGestation() const;
  void CalcLandscape() const;
public:
  cAnalyzeGenotype(cString symbol_string, cInstSet & in_inst_set);
  cAnalyzeGenotype(const cGenome & _genome, cInstSet & in_inst_set);
  cAnalyzeGenotype(const cAnalyzeGenotype & _gen);
  ~cAnalyzeGenotype();

  const cStringList & GetSpecialArgs() { return special_args; }
  void SetSpecialArgs(const cStringList & _args) { special_args = _args; }

  void Recalculate(cAnalyzeGenotype * parent_genotype=NULL);
  void PrintTasks(std::ofstream & fp, int min_task=0, int max_task=-1);

  // Set...
  void SetSequence(cString _sequence);
  
  void SetName(const cString & _name) { name = _name; }
  void SetAlignedSequence(const cString & _seq) { aligned_sequence = _seq; }
  void SetTag(const cString & _tag) { tag = _tag; }

  void SetViable(bool _viable) { viable = _viable; }

  void SetID(int _id) { id_num = _id; }
  void SetParentID(int _id) { parent_id = _id; }
  void SetParent2ID(int _id) { parent2_id = _id; }
  void SetNumCPUs(int _cpus) { num_cpus = _cpus; }
  void SetTotalCPUs(int _cpus) { total_cpus = _cpus; }
  void SetUpdateBorn(int _born) { update_born = _born; }
  void SetUpdateDead(int _dead) { update_dead = _dead; }
  void SetDepth(int _depth) { depth = _depth; }

  void SetLength(int _length) { length = _length; }
  void SetCopyLength(int _length) { copy_length = _length; }
  void SetExeLength(int _length) { exe_length = _length; }
  void SetMerit(double _merit) { merit = _merit; }
  void SetGestTime(int _gest) { gest_time = _gest; }
  void SetFitness(double _fitness) { fitness = _fitness; }
  void SetDivType(double _div_type) { div_type = _div_type; }
  void SetParentDist(int _dist) { parent_dist = _dist; }
  void SetAncestorDist(int _dist) { ancestor_dist = _dist; }
  void SetLineageLabel(int _label) { lineage_label = _label; }

  void SetParentMuts(const cString & in_muts) { parent_muts = in_muts; }
  void SetTaskOrder(const cString & in_order) { task_order = in_order; }

//    void SetFracDead(double in_frac);
//    void SetFracNeg(double in_frac);
//    void SetFracNeut(double in_frac);
//    void SetFracPos(double in_frac);

  // Accessors...
  const cGenome & GetGenome() const { return genome; }
  const cString & GetName() const { return name; }
  const cString & GetAlignedSequence() const { return aligned_sequence; }
  const cString & GetTag() const { return tag; }

  bool GetViable() const { return viable; }

  int GetID() const { return id_num; }
  int GetParentID() const { return parent_id; }
  int GetParent2ID() const { return parent2_id; }
  int GetParentDist() const { return parent_dist; }
  int GetAncestorDist() const { return ancestor_dist; }
  int GetLineageLabel() const { return lineage_label; }
  int GetNumCPUs() const { return num_cpus; }
  int GetTotalCPUs() const { return total_cpus; }
  int GetLength() const { return length; }
  int GetCopyLength() const { return copy_length; }
  int GetExeLength() const { return exe_length; }
  int GetMinLength() const { return Min(exe_length, copy_length); }
  double GetMerit() const { return merit; }
  double GetCompMerit() const { return merit / (double) GetMinLength(); }
  int GetGestTime() const { return gest_time; }
  double GetEfficiency() const
    { return ((double) GetMinLength()) / (double) gest_time; }
  double GetFitness() const { return fitness; }
  double GetDivType() const { return div_type; }
  int GetUpdateBorn() const { return update_born; }
  int GetUpdateDead() const { return update_dead; }
  int GetDepth() const { return depth; }

  const cString & GetParentMuts() const { return parent_muts; }

  double GetFracDead() const;
  double GetFracNeg() const;
  double GetFracNeut() const;
  double GetFracPos() const;

  double GetFitnessRatio() const { return fitness_ratio; }
  double GetEfficiencyRatio() const { return efficiency_ratio; }
  double GetCompMeritRatio() const { return comp_merit_ratio; }

  const cString & GetTaskOrder() const { return task_order; }
  cString GetTaskList() const;

  cString GetSequence() const { return genome.AsString(); }
  cString GetHTMLSequence() const;

  cString GetMapLink() const {
    return cStringUtil::Stringf("<a href=\"tasksites.%s.html\">Phenotype Map</a>", GetName()());
  }

  int GetNumTasks() const { return task_counts.GetSize(); }
  int GetTaskCount(int task_id) const {
    if (task_id >= task_counts.GetSize()) return 0;
    if (special_args.HasString("binary")) return (task_counts[task_id] > 0);
    return task_counts[task_id];
  }

  // Comparisons...  Compares a genotype to the "previous" one, which is
  // passed in, in one specified phenotype.
  // Return values are:
  //   -2 : Toggle; no longer has phenotype it used to...
  //   -1 : Reduction in strength of phenotype
  //    0 : Identical in phenotype
  //   +1 : Improvement in phenotype
  //   +2 : Toggle; phenotype now present that wasn't.
  int CompareNULL(cAnalyzeGenotype * prev) const { (void) prev; return 0; }
  int CompareArgNULL(cAnalyzeGenotype * prev, int i) const
    { (void) prev; (void) i;  return 0; }
  int CompareLength(cAnalyzeGenotype * prev) const {
    if (GetLength() < MIN_CREATURE_SIZE &&
	prev->GetLength() > MIN_CREATURE_SIZE) return -2;
    if (GetLength() > MIN_CREATURE_SIZE &&
	prev->GetLength() < MIN_CREATURE_SIZE) return 2;
    return 0;
  }
  int CompareMerit(cAnalyzeGenotype * prev) const
    { return NumCompare(GetMerit(), prev->GetMerit()); }
  int CompareCompMerit(cAnalyzeGenotype * prev) const
    { return NumCompare(GetCompMerit(), prev->GetCompMerit()); }
  int CompareGestTime(cAnalyzeGenotype * prev) const {
    const int max_time = CalcMaxGestation();
    const int cur_time = max_time - GetGestTime();
    const int prev_time = max_time - prev->GetGestTime();
    return NumCompare(cur_time, prev_time);
  }
  int CompareEfficiency(cAnalyzeGenotype * prev) const
    { return NumCompare(GetEfficiency(), prev->GetEfficiency()); }
  int CompareFitness(cAnalyzeGenotype * prev) const
    { return NumCompare(GetFitness(), prev->GetFitness()); }
  int CompareTaskCount(cAnalyzeGenotype * prev, int task_id) const
    { return NumCompare(GetTaskCount(task_id), prev->GetTaskCount(task_id)); }

  /*
  added to satisfy Boost.Python; the semantics are fairly useless --
  equality of two references means that they refer to the same object.
  */
  bool operator==(const cAnalyzeGenotype &in) const { return &in == this; }
};

#endif
