
#include "ImwPlatformWindow.h"

#include "ImwWindowManager.h"

namespace ImWindow
{
//SFF_BEGIN
	ImwPlatformWindow::ImwPlatformWindow(bool bMain, bool bIsDragWindow, bool bCreateState)
	{
		m_bMain = bMain;
		m_bIsDragWindow = bIsDragWindow;
		m_pContainer = new ImwContainer(this);
		
		m_pContext = NULL;
		m_pPreviousContext = NULL;

		if (bCreateState)
		{
			m_pContext = ImGui::CreateContext();
		}
	}

	ImwPlatformWindow::~ImwPlatformWindow()
	{
		ImwSafeDelete(m_pContainer);

		if (NULL != m_pContext)
			ImGui::DestroyContext(m_pContext);
	}

	bool ImwPlatformWindow::Init(ImwPlatformWindow* /*pParent*/)
	{
		return true;
	}

	const ImVec2 c_oVec2_0 = ImVec2(0,0);
	const ImVec2& ImwPlatformWindow::GetPosition() const
	{
		return c_oVec2_0;
	}

	const ImVec2& ImwPlatformWindow::GetSize() const
	{
		return ImGui::GetIO().DisplaySize;
	}

	void ImwPlatformWindow::Show()
	{
	}

	void ImwPlatformWindow::Hide()
	{
	}

	void ImwPlatformWindow::SetSize(int /*iWidth*/, int /*iHeight*/)
	{
	}

	void ImwPlatformWindow::SetPosition(int /*iX*/, int /*iY*/)
	{
	}

	void ImwPlatformWindow::SetTitle(const char* /*pTtile*/)
	{
	}

	void ImwPlatformWindow::OnClose()
	{
		ImwWindowManager::GetInstance()->OnClosePlatformWindow(this);
	}

	static bool s_bStatePush = false;

	bool ImwPlatformWindow::IsStateSet()
	{
		return s_bStatePush;
	}

	void ImwPlatformWindow::SetState()
	{
		IM_ASSERT(s_bStatePush == false);
		s_bStatePush = true;

		m_pPreviousContext = ImGui::GetCurrentContext();
		ImGui::SetCurrentContext(m_pContext);
	}

	void ImwPlatformWindow::RestoreState()
	{
		IM_ASSERT(s_bStatePush == true);
		s_bStatePush = false;

		ImGui::SetCurrentContext(m_pPreviousContext);
	}

	void ImwPlatformWindow::OnLoseFocus()
	{
		if (NULL != m_pContext)
		{
			m_pContext->SetNextWindowPosCond = 0;
			m_pContext->SetNextWindowSizeCond = 0;
			m_pContext->SetNextWindowContentSizeCond = 0;
			m_pContext->SetNextWindowCollapsedCond = 0;
			m_pContext->SetNextWindowFocus = 0;
		}
	}

	void ImwPlatformWindow::PreUpdate()
	{
	}

	void ImwPlatformWindow::Destroy()
	{
	}

	void ImwPlatformWindow::StartDrag()
	{
	}

	void ImwPlatformWindow::StopDrag()
	{
	}

	bool ImwPlatformWindow::IsDraging()
	{
		return false;
	}

	void ImwPlatformWindow::Paint()
	{
		ImwWindowManager::GetInstance()->Paint(this);
	}

	bool ImwPlatformWindow::IsMain()
	{
		return m_bMain;
	}

	void ImwPlatformWindow::Dock(ImwWindow* pWindow)
	{
		m_pContainer->Dock(pWindow);
	}

	bool ImwPlatformWindow::UnDock(ImwWindow* pWindow)
	{
		return m_pContainer->UnDock(pWindow);
	}

	ImwContainer* ImwPlatformWindow::GetContainer()
	{
		return m_pContainer;
	}

	ImwContainer* ImwPlatformWindow::HasWindow(ImwWindow* pWindow)
	{
		return m_pContainer->HasWindow(pWindow);
	}

	bool ImwPlatformWindow::FocusWindow(ImwWindow* pWindow)
	{
		return m_pContainer->FocusWindow(pWindow);
	}

	void ImwPlatformWindow::PaintContainer()
	{
		m_pContainer->Paint();
	}
//SFF_END
}