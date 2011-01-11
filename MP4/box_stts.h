#include "box.h"
#include <string>
#include <vector>

struct stts_record {
  uint32_t SampleCount;
  uint32_t SampleDelta;
};//stsc_record

class Box_stts {
  public:
    Box_stsc( );
    ~Box_stsc();
    Box * GetBox();
    void SetReserved( );
    void AddEntry( uint32_t SampleCount, uint32_t SampleDelta, uint32_t Offset = 0 );
  private:
    Box * Container;

    void WriteEntries( );
    std::vector<stts_record> Entries;
};//Box_ftyp Class

