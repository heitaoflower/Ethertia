//
// Created by Dreamtowards on 2023/1/18.
//

#ifndef ETHERTIA_COMMANDMESH_H
#define ETHERTIA_COMMANDMESH_H


class CommandMesh : public Command
{
public:

    void onCommand(const std::vector<std::string>& args) override
    {
        EntityPlayer* player = Ethertia::getPlayer();

        if (args[1] == "new")
        {
            EntityMesh* entity = new EntityMesh();
            Ethertia::getWorld()->addEntity(entity);
            entity->position() = player->position();

            const VertexData* vtx = MaterialMeshes::STOOL;
            entity->setMesh(EntityMesh::CreateMeshShape(vtx));
            entity->updateModel(Loader::LoadVertexData(vtx));

            _SendMessage("EntityMesh created.");
        }
        else
        {
            Entity* target = Ethertia::getHitCursor().hitEntity;
            if (!target) {
                _SendMessage("failed, no target entity.");
                return;
            }

            if (args[1] == "set")
            {
                const std::string& path = args[2];
                if (!Loader::FileExists(path)){
                    _SendMessage("No mesh file on: ", path);
                    return;
                }

                EntityMesh* eMesh = (EntityMesh*)target;

                auto vtx = Loader::LoadOBJ(path.c_str());
                eMesh->updateModel(Loader::LoadVertexData(vtx));
                eMesh->setMesh(EntityMesh::CreateMeshShape(vtx.get()));

                _SendMessage("Mesh updated.");
            }
            else if (args[1] == "diff")
            {
                const std::string& path = args[2];
                if (!Loader::FileExists(path)){
                    _SendMessage("No texture file on: ", path);
                    return;
                }

                EntityMesh* entity = (EntityMesh*)Ethertia::getHitCursor().hitEntity;
                entity->m_DiffuseMap = Loader::LoadImage(path);

                _SendMessage("Texture updated.");
            }
            else if (args[1] == "delete")
            {
                Ethertia::getWorld()->removeEntity(target);

                _SendMessage("Entity deleted.");
            }

        }
    }

};

#endif //ETHERTIA_COMMANDMESH_H
