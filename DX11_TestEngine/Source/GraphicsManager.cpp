#include "GraphicsManager.h"
#include "BasicExceptions.h"
#include "Text/FW1FontWrapper.h"
#include <sstream>
#include <d3dcompiler.h>


#pragma comment(lib, "d3d11.lib") //linka com a lib necessaria
#pragma comment(lib, "D3DCompiler.lib") //linka com a lib necessaria

using namespace Microsoft;
using namespace Matrices;

GraphicsManager::GraphicsManager(HWND _windowHandler)
{
	HRESULT result;
	DXGI_SWAP_CHAIN_DESC swapDescription = {};
	// nao esquecer que os ComPtr dao overload em '&', & da release automaticamente
	WRL::ComPtr<ID3D11Resource> backBuffer; //importante usar os ComPtr, pq eles dao release automaticamente
	
	swapDescription.BufferDesc.Width = 0; // Usar a width do windowHandler
	swapDescription.BufferDesc.Height = 0; // Usar a width do windowHandler
	swapDescription.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // formato dos pixels
	swapDescription.BufferDesc.RefreshRate.Numerator = 0; // Usa o RefreshRate do windows
	swapDescription.BufferDesc.RefreshRate.Denominator = 0; // Usa o RefreshRate do windows
	swapDescription.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED; // Como o app ta windowed, nao usa scaling
	swapDescription.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED; //interlaced?
	swapDescription.SampleDesc.Count = 1; // removerndo AA
	swapDescription.SampleDesc.Quality = 0; // removendo AA
	swapDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; //especifica que esse swap vai ser enviado como output
	swapDescription.BufferCount = 1; //Quantidade de double buffers(back e front)
	swapDescription.OutputWindow = _windowHandler; 
	swapDescription.Windowed = TRUE; 
	swapDescription.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapDescription.Flags = 0;

	result = D3D11CreateDeviceAndSwapChain(
		nullptr,					// deixa ele escolher o que ja esta sendo usado
		D3D_DRIVER_TYPE_HARDWARE,	// especifica que vamos usar a placa grafica fisica, nao uma virtual
		nullptr,					// Handler para o driver que vai simular a placa graphica virtual
		0,							// Flags
		nullptr,					// Especifica quais features vamos usar, null=todas que estiverem disponiveis
		0,							// numero de features
		D3D11_SDK_VERSION,			// especifica qual versao do SDK do d3d11 vamos usar, no caso, deixamos o sistema pegar o que estamos usando
		&swapDescription,			// pp, vale lembrar de D3D11 eh mt baseado em COM
		&m_swap,					// pp
		&m_device,					// pp
		nullptr,					// pp para o lance de features
		&m_context					// pp
	);
	BasicExceptions::CheckHResult(result);

	/*
	D3D_FEATURE_LEVEL featureLevelsRequested = D3D_FEATURE_LEVEL_11_1;
	const D3D_FEATURE_LEVEL featureLevel[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_12_1
	};

	result = D3D11CreateDeviceAndSwapChain(
		nullptr,					// deixa ele escolher o que ja esta sendo usado
		D3D_DRIVER_TYPE_HARDWARE,	// especifica que vamos usar a placa grafica fisica, nao uma virtual
		nullptr,					// Handler para o driver que vai simular a placa graphica virtual
		0,							// Flags
		featureLevel,				// Especifica quais features vamos usar, null=todas que estiverem disponiveis
		_countof(featureLevel),		// numero de features
		D3D11_SDK_VERSION,			// especifica qual versao do SDK do d3d11 vamos usar, no caso, deixamos o sistema pegar o que estamos usando
		&swapDescription,			// pp, vale lembrar de D3D11 eh mt baseado em COM
		&m_swap,					// pp
		&m_device,					// pp
		&featureLevelsRequested,	// pp para o lance de features
		&m_context					// pp
	);
	*/
	

	result = m_swap->GetBuffer(
		0, //0 = back buffer
		__uuidof(ID3D11Resource), // COM UUID
		&backBuffer // casta com base no UUID
	);
	BasicExceptions::CheckHResult(result);

	result = m_device->CreateRenderTargetView(
		backBuffer.Get(), 
		nullptr,
		&m_renderTargetView
	);
	BasicExceptions::CheckHResult(result);

	backBuffer->Release();
}


GraphicsManager::~GraphicsManager()
{
	/* removido a baixo por causa do uso de smart pointers
	// Free PPs
	if (m_renderTargetView != nullptr) //tem que verificar se o COM realmente conseguiu alocar o objeto
		m_renderTargetView->Release(); 
	if (m_context != nullptr) //tem que verificar se o COM realmente conseguiu alocar o objeto
		m_context->Release();
	if (m_swap != nullptr) //tem que verificar se o COM realmente conseguiu alocar o objeto
		m_swap->Release();
	if (m_device != nullptr) //tem que verificar se o COM realmente conseguiu alocar o objeto
		m_device->Release();
	*/
}

void GraphicsManager::RenderText()
{
	IFW1Factory* pFW1Factory;
	HRESULT hResult = FW1CreateFactory(FW1_VERSION, &pFW1Factory);

	IFW1FontWrapper* pFontWrapper;
	hResult = pFW1Factory->CreateFontWrapper(m_device.Get(), L"Arial", &pFontWrapper);

	for (int i = 0; i < m_textToRender.size(); i++)
	{		
		pFontWrapper->DrawString(
			m_context.Get(),
			m_textToRender[i].text,// String
			m_textToRender[i].size,// Font size
			m_textToRender[i].position.x,// X position
			m_textToRender[i].position.y,// Y position
			m_textToRender[i].color,// Text color, 0xAaBbGgRr
			FW1_RESTORESTATE + FW1_CENTER// Flags (for example FW1_RESTORESTATE to keep context states unchanged)
		);
	}
	pFontWrapper->Release();
	pFW1Factory->Release();
}

void GraphicsManager::DrawText(LPCWSTR _text, Vector2::Vec2D _pos, float _size, Vector4::Vec4D _color)
{
	m_textToRender.push_back(TextInfo(_text, _pos, _size, _color));
}

void GraphicsManager::ClearText()
{
	m_textToRender.clear();
}

void GraphicsManager::ShipFrame(std::shared_ptr<IGeometryDataStructure> _geometry)
{
	D3D11_VIEWPORT viewPort;
	float color[] = { 0.0f, 0.0f , 0.0f , 1.0f };
	std::shared_ptr<GraphicElement> element;
	ConstantBuffer elementBuffer;
	Matrix4x4 mvp;
	int size;
	//view.SetElement(0, 0, 0);
	//view.SetElement(1, 1, 0);
	//view.SetElement(2, 2, 0);
	//view.SetElement(3, 2, 10);

	//_geometry.get()->GetProjectionMatrix()->SetElement();

	m_context->ClearRenderTargetView(m_renderTargetView.Get(), color);

	//elementBuffer.Time = 0.0f;
	elementBuffer = {};
	elementBuffer.GlobalLight = *(_geometry.get()->GetGlobalLight());
	if (_geometry.get() != nullptr)
	{
		size = _geometry.get()->size();
		for (int i = 0; i < size; i++)
		{
			element = _geometry.get()->get_item(i);
			//element.get()->CalculateNormals();

			mvp = element.get()->GetTransform() * (*(_geometry.get()->GetViewMatrix()));
			mvp = mvp * (*(_geometry.get()->GetProjectionMatrix()));
			for (int j = 0; j < 16; j++) elementBuffer.GeometryMVP[j] = mvp.GetElement(j);
			elementBuffer.RenderFlags = element.get()->GetRenderFlags();

			DrawGeometry(&(element.get()->GetGeometry()[0]), elementBuffer, element->GetGeometry().size());
		}
	}


	// bind render target
	m_context->OMSetRenderTargets(1u, m_renderTargetView.GetAddressOf(), nullptr);
	// configure viewport
	viewPort = {};
	viewPort.Width = WIDTH;
	viewPort.Height = HEIGHT;
	viewPort.MinDepth = 0;
	viewPort.MaxDepth = 1;
	viewPort.TopLeftX = 0;
	viewPort.TopLeftY = 0;
	m_context->RSSetViewports(1u, &viewPort);

	RenderText();

	BasicExceptions::CheckHResult(m_swap->Present(1u, 0u));
}

void GraphicsManager::NormalizeGeometry(GraphicElement& _graphicElement)
{
	VertexColor* elementGeometry;
	int geometrySize;
	Vector3::Vec3D pos = _graphicElement.GetPosition();
	Vector3::Vec3D size = _graphicElement.GetScale();

	//_graphicElement.GetGeometry(&elementGeometry, &geometrySize);
	geometrySize = 0;
	elementGeometry = nullptr;
	for (int i = 0; i < geometrySize; i++)
	{
		elementGeometry[i].pos.x *= size.x;
		elementGeometry[i].pos.y *= size.y;
		elementGeometry[i].pos.z *= size.z;
		elementGeometry[i].pos.x += pos.x;
		elementGeometry[i].pos.y += pos.y;
		elementGeometry[i].pos.z += pos.z;

		elementGeometry[i].pos.y *= (float)WIDTH / (float)HEIGHT;
	}
}

void GraphicsManager::DrawGeometry(VertexColor* _vertices, ConstantBuffer& _geometryMVP, int _verticesLength)
{
	if (_verticesLength == 0)
		return;
	
	WRL::ComPtr<ID3D11Buffer> vertexBuffer;
	WRL::ComPtr<ID3D11VertexShader> vertexShader;
	WRL::ComPtr<ID3D11PixelShader> pixelShader;
	WRL::ComPtr<ID3D11GeometryShader> geometryShader;
	WRL::ComPtr<ID3DBlob> binaryBlob;
	WRL::ComPtr<ID3D11InputLayout> inputLayoutPixel;
	WRL::ComPtr<ID3D11InputLayout> inputLayoutVertex;
	WRL::ComPtr<ID3D11Buffer> constantBuffer;

	D3D11_VIEWPORT viewPort;
	D3D11_BUFFER_DESC bufferDescription;
	D3D11_BUFFER_DESC constantBufferDescription;
	D3D11_SUBRESOURCE_DATA vertexSubresData;
	D3D11_SUBRESOURCE_DATA constBufferSubresData;
	// Pipeline params
	const UINT stride = sizeof(VertexColor);
	const UINT offset = 0u;

	//-----GEOMETRY BUFFER DESCRIPTION-----//
	bufferDescription = {};
	bufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDescription.Usage = D3D11_USAGE_DEFAULT;
	bufferDescription.CPUAccessFlags = 0u;
	bufferDescription.MiscFlags = 0u;
	bufferDescription.ByteWidth = sizeof(VertexColor) * _verticesLength;
	bufferDescription.StructureByteStride = sizeof(VertexColor);
	//-----GEOMETRY BUFFER DESCRIPTION-----//


	//Matrices::Matrix4x4 scaleMatrix;
	//
	//scaleMatrix.SetElement(0, 0, (float)HEIGHT / (float)WIDTH);
	//scaleMatrix.SetElement(1, 1, 1.0f);
	//scaleMatrix.SetElement(2, 2, 1.0f);
	//
	//_geometryTransform = _geometryTransform * scaleMatrix;

	//-----CONSTANT BUFFER DESCRIPTION-----//
	constantBufferDescription = {};
	constantBufferDescription.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBufferDescription.Usage = D3D11_USAGE_DYNAMIC;
	constantBufferDescription.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	constantBufferDescription.MiscFlags = 0u;
	constantBufferDescription.ByteWidth = sizeof(ConstantBuffer);
	constantBufferDescription.StructureByteStride = 0u;
	constBufferSubresData = {};
	constBufferSubresData.pSysMem = &_geometryMVP;
	constBufferSubresData.SysMemPitch = 0;
	constBufferSubresData.SysMemSlicePitch = 0;
	BasicExceptions::CheckHResult(m_device->CreateBuffer(&constantBufferDescription, &constBufferSubresData, &constantBuffer));

	m_context->VSSetConstantBuffers(0u, 1u, constantBuffer.GetAddressOf());
	m_context->GSSetConstantBuffers(0u, 1u, constantBuffer.GetAddressOf());
	m_context->PSSetConstantBuffers(0u, 1u, constantBuffer.GetAddressOf());
	//-----CONSTANT BUFFER DESCRIPTION-----//

	
	vertexSubresData = {};
	vertexSubresData.pSysMem = _vertices;
	BasicExceptions::CheckHResult(m_device->CreateBuffer(&bufferDescription, &vertexSubresData, &vertexBuffer));

	// Bind vertex buffer to pipeline
	m_context->IASetVertexBuffers(0u, 1u, vertexBuffer.GetAddressOf(), &stride, &offset);

	//Geometry shader:
	// create Geometry shader
	BasicExceptions::CheckHResult(D3DReadFileToBlob(L"Source/GeometryShader.cso", &binaryBlob));
	BasicExceptions::CheckHResult(m_device->CreateGeometryShader(binaryBlob->GetBufferPointer(), binaryBlob->GetBufferSize(), nullptr, &geometryShader));
	// bind Geometry shader
	m_context->GSSetShader(geometryShader.Get(), nullptr, 0u);

	//PIXEL:
	// create pixel shader
	BasicExceptions::CheckHResult(D3DReadFileToBlob(L"Source/PixelShader.cso", &binaryBlob));
	BasicExceptions::CheckHResult(m_device->CreatePixelShader(binaryBlob->GetBufferPointer(), binaryBlob->GetBufferSize(), nullptr, &pixelShader));
	// bind pixel shader
	m_context->PSSetShader(pixelShader.Get(), nullptr, 0u);
	/*// input (pixel) layout (2d position only)
	const D3D11_INPUT_ELEMENT_DESC inputDescription[] =
	{
		{ "Pos",0,DXGI_FORMAT_R32G32B32A32_FLOAT,1,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
	};
	BasicExceptions::CheckHResult(m_device->CreateInputLayout(
		inputDescription, (UINT)std::size(inputDescription),
		binaryBlob->GetBufferPointer(),
		binaryBlob->GetBufferSize(),
		&inputLayoutPixel
	));
	
	// bind pixel layout
	m_context->IASetInputLayout(inputLayoutPixel.Get());
	*/




	//VERTEX:
	// create vertex shader
	BasicExceptions::CheckHResult(D3DReadFileToBlob(L"Source/VertexShader.cso", &binaryBlob));
	BasicExceptions::CheckHResult(m_device->CreateVertexShader(binaryBlob->GetBufferPointer(), binaryBlob->GetBufferSize(), nullptr, &vertexShader));
	// bind vertex shader
	m_context->VSSetShader(vertexShader.Get(), nullptr, 0u);


	const D3D11_INPUT_ELEMENT_DESC inputDescription[] =
	{
		{ "POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "NORMAL",0,DXGI_FORMAT_R32G32B32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "COLOR",0, DXGI_FORMAT_R8G8B8A8_UNORM,0, D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0 }
	};
	BasicExceptions::CheckHResult(m_device->CreateInputLayout(
		inputDescription, (UINT)std::size(inputDescription),
		binaryBlob->GetBufferPointer(),
		binaryBlob->GetBufferSize(),
		&inputLayoutVertex
	));

	// bind vertex layout
	m_context->IASetInputLayout(inputLayoutVertex.Get());

	// Set primitive topology to triangle list (groups of 3 vertices)
	m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


	m_context->Draw((UINT)_verticesLength, 0u);
}
