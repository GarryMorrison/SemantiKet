#pragma once

class Serial  // Not sure this is the best place for this, but will do for now!
{
public:
    void reset_id() { m_serial_id = 0; }
    int get_id() { m_serial_id++; return m_serial_id; }
private:
    int m_serial_id = 0;
};
