/* Minimal shared export base for CLI exporters.
 * This provides a minimal definition for `PCB_EXPORT_BASE_COMMAND` used
 * by several non-pcb commands (footprint, schematic exporters) so that
 * removing the PCB editor CLI sources does not break shared exporters.
 *
 * This is intentionally small: it mainly forwards to CLI::COMMAND and
 * exposes helper methods used by callers in this tree.
 */

#ifndef COMMAND_PCB_EXPORT_BASE_H
#define COMMAND_PCB_EXPORT_BASE_H

#include "command.h"

namespace CLI
{
class PCB_EXPORT_BASE_COMMAND : public COMMAND
{
public:
    PCB_EXPORT_BASE_COMMAND( const std::string& aName, IO_TYPE aInputType = IO_TYPE::FILE, IO_TYPE aOutputType = IO_TYPE::FILE )
        : COMMAND( aName )
    {
        addCommonArgs( true, true, aInputType, aOutputType );
    }

protected:
    void addLayerArg()
    {
        m_argParser.add_argument( "--layers" )
            .default_value( std::string() )
            .help( UTF8STDSTR( _( "Comma-separated list of layers to export (e.g. F.Cu,B.Cu)" ) ) );
    }

    void addDefineArg()
    {
        // expose the common define variable handler from the base class
        COMMAND::addDefineArg();
    }
};

} // namespace CLI

#endif
