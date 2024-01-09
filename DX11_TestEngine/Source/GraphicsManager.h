#pragma once

#include "CustomWinInclude.h"
#include "Common.h"
#include "GraphicElement.h"
#include "Matrices.h"
#include "IGeometryDataStructure.h"
#include <wrl.h>
#include <d3d11.h>
#include <vector>
#include <memory>


class GraphicsManager
{
private:
	struct TextInfo
	{
		LPCWSTR text;
		Vector2::Vec2D position;
		Vector4::Vec4D color;
		float size;
		TextInfo(LPCWSTR _text, Vector2::Vec2D _pos, float _size, Vector4::Vec4D _color) : text(_text), position(_pos), size(_size), color(_color) {}
	};

	struct ConstantBuffer
	{
		float GeometryMVP[16];
		unsigned int RenderFlags;
		Vector3::Vec3D GlobalLight;
	};
	/// <summary>
	/// Especifica como o recurso que esta atrelado a esse RTV deve ser usado pelo driver da GPU
	/// </summary>
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_renderTargetView;

	/// <summary>
	/// Device representa a placa de video e suas capacidades.
	/// Pode ser de fato um controlador da placa de video, 
	/// ou uma virutalizacao por software;
	/// </summary>
	Microsoft::WRL::ComPtr<ID3D11Device> m_device;

	/// <summary>
	/// Agrega os frame buffers
	/// Tem os back e front buffers
	/// </summary>
	Microsoft::WRL::ComPtr<IDXGISwapChain> m_swap;

	/// <summary>
	/// Representa o dispositivo grafico, 
	/// envia comandos e derenderizacao e de controle do pipeline grafico
	/// </summary>
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_context;
	std::vector<TextInfo> m_textToRender;


	void DrawGeometry(VertexColor* _vertices, ConstantBuffer& _geometryMVP, int _verticesLength);
	void RenderText();
	void NormalizeGeometry(GraphicElement& _graphicElement);
public:
	GraphicsManager(const GraphicsManager&) = delete;
	GraphicsManager& operator=(const GraphicsManager&) = delete;

	GraphicsManager(HWND _windowHandler);
	~GraphicsManager();

	void ShipFrame(std::shared_ptr<IGeometryDataStructure> _geometry);
	void DrawText(LPCWSTR _text, Vector2::Vec2D _pos, float _size, Vector4::Vec4D _color = Vector4::Vec4One);
	void ClearText();

};

