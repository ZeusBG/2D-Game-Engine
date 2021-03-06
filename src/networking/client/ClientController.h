#pragma once
#include <string>
#include <vector>
#include <memory>
#include "networking/NetworkManager.h"

struct ByteStream;
class Peer;
class Client;
class GameClient;
class Entity;

class ClientController : public NetworkManager
{
	std::shared_ptr<Client> m_Client;
	std::string m_ServerIp;
	unsigned int m_ServerPort;
	std::shared_ptr<Entity> m_Player;
public:
	ClientController();
	~ClientController();

	virtual void HandleRecievedPackets() override;
	virtual void SendPendingPackets() override;
	virtual void OnEntityRemoved(const Entity* entity) override {};
	virtual void DoSnapShot() override;
	virtual void Init(const char* ip, int port) override;
	
	void UnpackRecievedData(ByteStream& bs);
	void SpawnEntity(int entityTypeId, int id);
	void Start();
	void SendDataTo(const ByteStream* data);
};