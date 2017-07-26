#include "engine/rendering/Mesh.h"
#include "engine/object/VisualComponent.h"

void Mesh::SetVertices(const AVector<XMFLOAT2>& vertices)
{
    m_Vertices = vertices;
}

void Mesh::AddVertex(float x, float y)
{
    m_Vertices.push_back({ x,y });
}

void Mesh::InitializeBuffers(ID3D11Device* device, VisualComponent* visualComponent)
{
    //Vertex* vertices;
    //unsigned long* indices;
    D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
    D3D11_SUBRESOURCE_DATA vertexData, indexData;

    ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
    ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));
    ZeroMemory(&vertexData, sizeof(vertexData));
    ZeroMemory(&indexData, sizeof(indexData));
    HRESULT result;
   
    // Load the vertex array with data.
    // Set up the description of the static vertex buffer.
    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    vertexBufferDesc.ByteWidth = sizeof(XMFLOAT2) * m_Vertices.size();
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    // Give the subresource structure a pointer to the vertex data.
    vertexData.pSysMem = m_Vertices.data();

    // Now create the vertex buffer.
    result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_VertexBuffer);
    // Set up the description of the static index buffer.
    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    indexBufferDesc.ByteWidth = sizeof(unsigned int)* m_Indices.size();
    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

    // Give the subresource structure a pointer to the index data.
    indexData.pSysMem = m_Indices.data();

    // Create the index buffer.
    result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_IndexBuffer);

    int a = 0;
}

void Mesh::RenderBuffers(ID3D11DeviceContext* deviceContext) const
{
    unsigned int stride;
    unsigned int offset;


    // Set vertex buffer stride and offset.
    stride = sizeof(XMFLOAT2);
    offset = 0;

    // Set the vertex buffer to active in the input assembler so it can be rendered.
    deviceContext->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

    // Set the index buffer to active in the input assembler so it can be rendered.
    deviceContext->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

    // Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    return;
}

void Mesh::ReleaseResource()
{
    // Release the index buffer.
    if (m_IndexBuffer)
    {
        m_IndexBuffer->Release();
        m_IndexBuffer = 0;
    }

    // Release the vertex buffer.
    if (m_VertexBuffer)
    {
        m_VertexBuffer->Release();
        m_VertexBuffer = 0;
    }

    return;
}

void Mesh::AddIndex(unsigned int i1, unsigned int i2, unsigned int i3)
{
    m_Indices.push_back(i1);
    m_Indices.push_back(i2);
    m_Indices.push_back(i3);
}
