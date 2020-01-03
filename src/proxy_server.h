#pragma once

//
// The ProxyServer watches for game packets coming from the remote server or
// the local PS3s and passes the packets through so that WarHawkReborn can
// act as an intermediary or "proxy" server.
// This requires the port forwarding to forward to the WarHawkReborn server
// instead of the local PS3 running WarHawk.
//

#include <functional>
#include <iostream>

#include "message_handler.h"
#include "server_list.h"
#include "udp_network_socket.h"


class Network;
class Packet;
class PacketProcessor;


class ProxyServer : public MessageHandler
{
  public:

    ProxyServer( ServerList &, PacketProcessor &, Network & );
    ~ProxyServer( );
 
    void OnReceivePacket( sockaddr_storage client, const Packet & ) override;

  protected:

  private:

    //
    // Methods
    //

    void OnHandleServerInfoRequest( const std::string &fromIp, const Packet & );
    void OnHandleServerInfoResponse( const Packet & );

    //
    // Data
    //

    ServerList      &m_ServerList;
    PacketProcessor &m_PacketProcessor;
    Network         &m_Network;
    bool             m_ProxyMode       = false;
    bool             m_ReplyingToQuery = false;
    std::string      m_ServerListServer; // warhawk.thalhamer.it.
    uint16_t         m_LastServerListServerPort; // Port we last received packet from ServerListServer on.
    std::vector < std::string > m_ClientIpList;
};
