/*
			This file is part of:
				NoahFrame
			https://github.com/ketoo/NoahGameFrame

   Copyright 2009 - 2019 NoahFrame(NoahGameFrame)

   File creator: lvsheng.huang

   NoahFrame is open-source software and you can redistribute it and/or modify
   it under the terms of the License; besides, anyone who use this file/software must include this copyright announcement.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

	   http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include "NFBluePrintView.h"
#include "NFUIModule.h"

NFBluePrintView::NFBluePrintView(NFIPluginManager* p, NFViewType vt) : NFIView(p, vt, GET_CLASS_NAME(NFBluePrintView))
{
   m_pNodeView = NF_NEW NFNodeView(p);
   m_pTreeView = NF_NEW NFTreeView(p);
   m_pNodeView->ResetOffest(NFVector2::Zero());

   m_pTreeView->SetSelectedNodeFunctor(std::bind(&NFBluePrintView::HandlerSelected, this, std::placeholders::_1));
   m_pTreeView->SetName(GET_CLASS_NAME(NFBluePrintView));

   m_pUIModule = pPluginManager->FindModule<NFIUIModule>();
   m_pBluePrintModule = pPluginManager->FindModule<NFIBluePrintModule>();
   m_pKernelModule = pPluginManager->FindModule<NFIKernelModule>();

   m_pBluePrintModule->SetLogicBlockEventFunctor(std::bind(&NFBluePrintView::ModifyEvent, this, std::placeholders::_1, std::placeholders::_2));
   /*
   NFGUID testID1 = m_pKernelModule->CreateGUID();
   NFGUID testID2 = m_pKernelModule->CreateGUID();
   NFGUID testID3 = m_pKernelModule->CreateGUID();
   NFGUID testID4 = m_pKernelModule->CreateGUID();
   NFGUID testID5 = m_pKernelModule->CreateGUID();


   m_pNodeView->AddNode(testID1, "testnode1111111", NFVector2(0, 100));
   m_pNodeView->AddNode(testID2, "testnode2222222", NFVector2(0, 200));
   m_pNodeView->AddNode(testID3, "testnode23333", NFVector2(200, 0));
   m_pNodeView->AddNode(testID4, "testnode4444", NFVector2(300, 0));
   m_pNodeView->AddNode(testID5, "testnode555", NFVector2(300, 300));
   */
/*
   	static NFGUID tree111 = m_pKernelModule->CreateGUID();
   	static NFGUID tree222 = m_pKernelModule->CreateGUID();
   	static NFGUID tree333 = m_pKernelModule->CreateGUID();
   	static NFGUID tree444 = m_pKernelModule->CreateGUID();


   	static NFGUID sub1 = m_pKernelModule->CreateGUID();
   	static NFGUID sub2 = m_pKernelModule->CreateGUID();
   	static NFGUID sub3 = m_pKernelModule->CreateGUID();
   	static NFGUID sub4 = m_pKernelModule->CreateGUID();
   	static NFGUID sub5 = m_pKernelModule->CreateGUID();
   	static NFGUID sub6 = m_pKernelModule->CreateGUID();


   	m_pTreeView->AddTreeNode(tree111, "tree111");
   	m_pTreeView->AddTreeNode(tree222, "tree222");
   	m_pTreeView->AddTreeNode(tree333, "tree333");
   	m_pTreeView->AddTreeNode(tree444, "tree444");
   	m_pTreeView->AddSubTreeNode(tree111, sub1, "sub1");
   	m_pTreeView->AddSubTreeNode(tree111, sub2, "sub2");
   	m_pTreeView->AddSubTreeNode(tree111, sub3, "sub3");
   	m_pTreeView->AddSubTreeNode(tree222, sub4, "sub4");
   	m_pTreeView->AddTreeLeafNode(tree222, sub5, "sub5");
   	m_pTreeView->AddTreeLeafNode(tree222, sub6, "sub6");
   //m_pNodeView->AddNode(testID3, "testnode333333", NFVector2(200, 0));
   //m_pNodeView->AddNode(testID4, "testnode4444444", NFVector2(300, 0));
*/
   //m_pNodeView->AddNodeAttrOut(testID1, m_pKernelModule->CreateGUID(), "Out1");
   //m_pNodeView->AddNodeAttrOut(testID1, m_pKernelModule->CreateGUID(), "Out2");
  // m_pNodeView->AddNodeAttrIn(testID2, m_pKernelModule->CreateGUID(), "In12");
   //m_pNodeView->AddNodeAttrIn(testID2, m_pKernelModule->CreateGUID(), "In123222");
   /*
   m_pNodeView->AddNodeAttrOut(testID2, m_pKernelModule->CreateGUID(), "Out1");
   m_pNodeView->AddNodeAttrOut(testID2, m_pKernelModule->CreateGUID(), "Out2");
   m_pNodeView->AddNodeAttrOut(testID3, m_pKernelModule->CreateGUID(), "Out1");
   m_pNodeView->AddNodeAttrOut(testID3, m_pKernelModule->CreateGUID(), "Out2");

   m_pNodeView->AddNodeAttrIn(testID1, m_pKernelModule->CreateGUID(), "In1");
   m_pNodeView->AddNodeAttrIn(testID1, m_pKernelModule->CreateGUID(), "In2");
   m_pNodeView->AddNodeAttrIn(testID2, m_pKernelModule->CreateGUID(), "In12");
   m_pNodeView->AddNodeAttrIn(testID2, m_pKernelModule->CreateGUID(), "In123222");
   m_pNodeView->AddNodeAttrIn(testID3, m_pKernelModule->CreateGUID(), "In13");
   m_pNodeView->AddNodeAttrIn(testID3, m_pKernelModule->CreateGUID(), "In133333");
   */
}

NFBluePrintView::~NFBluePrintView()
{
   delete m_pNodeView;
   m_pNodeView = nullptr;

   delete m_pTreeView;
   m_pTreeView = nullptr;
}

bool NFBluePrintView::Execute()
{
   ImGui::SameLine();
   if (ImGui::Button("- nodes"))
   {
   }

   ImGui::SameLine();
   if (ImGui::Button("- links"))
   {
   }

	ImGui::SameLine();
	if (ImGui::Button("return to center"))
	{
		m_pNodeView->ResetOffest(NFVector2::Zero());
	}

	ImGui::SameLine();

	std::string panning = "Panning(" + std::to_string((int)m_pNodeView->GetOffest().X()) + "," + std::to_string((int)m_pNodeView->GetOffest().Y()) + ")";
	ImGui::Button(panning.c_str());

	ImGui::SameLine();

	std::string origin = "origin(" + std::to_string((int)m_pNodeView->GetGridOringin().X()) + "," + std::to_string((int)m_pNodeView->GetGridOringin().Y()) + ")";
	ImGui::Button(origin.c_str());

   m_pNodeView->Execute();
   
   CreateLogicBlockWindow();
   CreateMonitor();
   CreateJudgment();
   CreateExecuter();
   CreateVariable();

   CreateComparator();

   if (ImGui::IsWindowFocused())
   {
      NF_SHARE_PTR<NFIView> pView = m_pUIModule->GetView(NFViewType::HierachyView);
      if (pView)
      {
         pView->OccupySubRender(this);
      }
   }

   ImGuiIO& io = ImGui::GetIO();
   if (io.KeyCtrl)
   {

   }

	return false;
}

void AddJudgementNode(NFTreeView* pTreeView, const NFGUID& parentID, NF_SHARE_PTR<NFJudgement> judgement);

void AddExecuterNode(NFTreeView* pTreeView, const NFGUID& id, NF_SHARE_PTR<NFExecuter> executer)
{
	pTreeView->AddSubTreeNode(id, executer->id, executer->name);
	if (executer->nextExecuter)
	{
		AddExecuterNode(pTreeView, executer->id, executer->nextExecuter);
	}
	
	for (auto it : executer->judgements)
	{
		AddJudgementNode(pTreeView, executer->id, it);
	}
}

void AddJudgementNode(NFTreeView* pTreeView, const NFGUID& parentID, NF_SHARE_PTR<NFJudgement> judgement)
{
	pTreeView->AddSubTreeNode(parentID, judgement->id, judgement->name);

	if (judgement->trueBlueprintNode)
	{
		if (judgement->trueBlueprintNode->blueprintType == NFBlueprintType::JUDGEMENT)
		{
			AddJudgementNode(pTreeView, judgement->id, std::dynamic_pointer_cast<NFJudgement>(judgement->trueBlueprintNode));
		}
		else if (judgement->trueBlueprintNode->blueprintType == NFBlueprintType::EXECUTER)
		{
			AddExecuterNode(pTreeView, judgement->id, std::dynamic_pointer_cast<NFExecuter>(judgement->trueBlueprintNode));
		}
	}

	if (judgement->falseBlueprintNode)
	{
		if (judgement->falseBlueprintNode->blueprintType == NFBlueprintType::JUDGEMENT)
		{
			AddJudgementNode(pTreeView, judgement->id, std::dynamic_pointer_cast<NFJudgement>(judgement->falseBlueprintNode));
		}
		else if (judgement->falseBlueprintNode->blueprintType == NFBlueprintType::EXECUTER)
		{
			AddExecuterNode(pTreeView, judgement->id, std::dynamic_pointer_cast<NFExecuter>(judgement->falseBlueprintNode));
		}
	}
}

NFGUID NFBluePrintView::GetCurrentObjectID()
{
	return mCurrentObjectID;
}

void NFBluePrintView::SetCurrentObjectID(const NFGUID& id)
{
	mCurrentObjectID = id;

	NFNodeView* pView = (NFNodeView*)m_pNodeView;

	pView->MoveToNode(mCurrentObjectID);
}

NFTreeView* NFBluePrintView::GetTreeView()
{
	return m_pTreeView;
}

NFNodeView* NFBluePrintView::GetNodeView()
{
	return m_pNodeView;
}

void NFBluePrintView::SubRender()
{
	//ImGui::GetIO().KeyCtrl)
   m_pTreeView->Execute();
}

void NFBluePrintView::HandlerSelected(const NFGUID& id)
{
	mCurrentObjectID = NFGUID();
	auto node = m_pBluePrintModule->FindBaseNode(id);
	if (node)
	{
		SetCurrentObjectID(id);
	}

	//referesh for sub window
	//occupy inspectorview
	NF_SHARE_PTR<NFIView> pHierachyView = m_pUIModule->GetView(NFViewType::HierachyView);
	NF_SHARE_PTR<NFIView> pInspectorView = m_pUIModule->GetView(NFViewType::InspectorView);
	if (pHierachyView && pInspectorView)
	{
		pInspectorView->OccupySubRender(pHierachyView.get());
	}
}

void NFBluePrintView::ModifyEvent(const NFGUID& id, const bool create)
{
	if (create)
	{
		auto node = m_pBluePrintModule->FindBaseNode(id);
		if (node->parent)
		{
			m_pTreeView->AddSubTreeNode(node->parent->id, node->id, node->name);
			m_pNodeView->AddNode(node->id, node->name, NFVector2(0, 0));
		}
		else
		{
			m_pTreeView->AddTreeNode(node->id, node->name);
		}
	}
	else
	{
		m_pTreeView->DeleteTreeNode(id);
		m_pNodeView->DeleteNode(id);
	}
	/*
	//m_pTreeView->Clear();
	//m_pNodeView->CleanNodes();

	const std::list<NF_SHARE_PTR<NFLogicBlock>>& logicBlocks = m_pBluePrintModule->GetLogicBlocks();
	for (auto block : logicBlocks)
	{
		m_pTreeView->AddTreeNode(block->id, block->name);

		for (auto monitor : block->monitors)
		{
			m_pTreeView->AddSubTreeNode(block->id, monitor->id, monitor->name);
			m_pNodeView->AddNode(monitor->id, monitor->name);

			for (auto judgement : monitor->judgements)
			{
				AddJudgementNode(m_pTreeView, monitor->id, judgement);
			}
		}

		for (auto variable : block->variables)
		{
			m_pTreeView->AddSubTreeNode(block->id, variable->id, variable->name);
			m_pNodeView->AddNode(variable->id, variable->name);
		}
	}
	*/

}

void NFBluePrintView::TryToCreateBluePrintBlock()
{
   if (!bCreatingLogicBlock)
   {
      bCreatingLogicBlock = true;
   }
}

void NFBluePrintView::TryToCreateMonitor()
{
	if (!bCreatingMonitor)
	{
		bCreatingMonitor = true;
	}
}

void NFBluePrintView::TryToCreateJudgement()
{
	if (!bCreatingJudgment)
	{
		bCreatingJudgment = true;
	}
}

void NFBluePrintView::TryToCreateExecuter()
{
	if (!bCreatingExecuter)
	{
		bCreatingExecuter = true;
	}
}

void NFBluePrintView::TryToCreateVariable()
{
	if (!bCreatingVariable)
	{
		bCreatingVariable = true;
	}
}

void NFBluePrintView::TryToCreateComparator()
{
	if (!bCreatingComparator)
	{
		bCreatingComparator = true;
	}
}

void NFBluePrintView::CreateLogicBlockWindow()
{
	if (bCreatingLogicBlock)
	{
		ImGui::OpenPopup("CreatingLogicBlock");
		ImGui::SetNextWindowSize(ImVec2(230, 150));

		if (ImGui::BeginPopupModal("CreatingLogicBlock"))
		{
			static char str0[128] = "Hello, Blueprint!";
			ImGui::InputText("LogicBlock Name", str0, IM_ARRAYSIZE(str0));

			ImGui::Separator();

			ImGui::Text("All those beautiful files will be deleted.\nThis operation cannot be undone!\n\n");

			ImGui::Separator();

			if (ImGui::Button("Cancel", ImVec2(100, 30)))
			{
			   bCreatingLogicBlock = false;
			   ImGui::CloseCurrentPopup();
			}

			ImGui::SameLine();

			if (ImGui::Button("OK", ImVec2(100, 30)))
			{
			   m_pBluePrintModule->CreateLogicBlock(m_pKernelModule->CreateGUID(), str0);
			   bCreatingLogicBlock = false;
			   ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}
	}
}

void NFBluePrintView::CreateMonitor()
{
	if (bCreatingMonitor)
	{
		auto currentLogicBlock = m_pBluePrintModule->FindBaseNode(GetCurrentObjectID());
		if (currentLogicBlock)
		{
			if (currentLogicBlock->blueprintType == NFBlueprintType::LOGICBLOCK)
			{
				ImGui::OpenPopup("Creating Monitor");
				ImGui::SetNextWindowSize(ImVec2(230, 150));

				if (ImGui::BeginPopupModal("Creating Monitor"))
				{
					static char str0[128] = "Hello, monitor";
					ImGui::InputText("Monitor Name", str0, IM_ARRAYSIZE(str0));

					ImGui::Separator();

					ImGui::Text("All those beautiful files will be deleted.\nThis operation cannot be undone!\n\n");

					ImGui::Separator();

					if (ImGui::Button("Cancel", ImVec2(100, 30)))
					{
						bCreatingMonitor = false;
						ImGui::CloseCurrentPopup();
					}

					ImGui::SameLine();

					if (ImGui::Button("OK", ImVec2(100, 30)))
					{
						m_pBluePrintModule->AddMonitorForLogicBlock(GetCurrentObjectID(), m_pKernelModule->CreateGUID(), str0);
						bCreatingMonitor = false;
						ImGui::CloseCurrentPopup();
					}

					ImGui::EndPopup();
				}
			}
         else
         {
            bCreatingMonitor = false;
         }
		}
      else
      {
		   bCreatingMonitor = false;
      }
	}
}

void NFBluePrintView::CreateJudgment()
{
	if (bCreatingJudgment)
	{
		auto currentObject = m_pBluePrintModule->FindBaseNode(mCurrentObjectID);
		if (currentObject)
		{
			if (currentObject->blueprintType == NFBlueprintType::MONITOR
				|| currentObject->blueprintType == NFBlueprintType::JUDGEMENT
				|| currentObject->blueprintType == NFBlueprintType::EXECUTER)
			{
				ImGui::OpenPopup("Creating Judgment");
				ImGui::SetNextWindowSize(ImVec2(230, 150));

				if (ImGui::BeginPopupModal("Creating Judgment"))
				{
					static char str0[128] = "Hello, Judgment!";
					ImGui::InputText("Judgment Name", str0, IM_ARRAYSIZE(str0));

					ImGui::Separator();

					ImGui::Text("All those beautiful files will be deleted.\nThis operation cannot be undone!\n\n");

					ImGui::Separator();

					if (ImGui::Button("Cancel", ImVec2(100, 30)))
					{
						bCreatingJudgment = false;
						ImGui::CloseCurrentPopup();
					}

					ImGui::SameLine();

					if (ImGui::Button("OK", ImVec2(100, 30)))
					{
						if (currentObject->blueprintType == NFBlueprintType::MONITOR)
						{
							m_pBluePrintModule->AddJudgementForMonitor(mCurrentObjectID, m_pKernelModule->CreateGUID(), str0);
						}
						else if (currentObject->blueprintType == NFBlueprintType::JUDGEMENT)
						{
							//m_pBluePrintModule->AddJudgementForJudgement(mCurrentObjectID, m_pKernelModule->CreateGUID(), str0);
						}
						else if (currentObject->blueprintType == NFBlueprintType::EXECUTER)
						{
							m_pBluePrintModule->AddJudgementForExecuter(mCurrentObjectID, m_pKernelModule->CreateGUID(), str0);
						}

						bCreatingJudgment = false;
						ImGui::CloseCurrentPopup();
					}

					ImGui::EndPopup();
				}
         }
         else
         {
            bCreatingJudgment = false;
         }
		}
      else
      {
		   bCreatingJudgment = false;
      }
	}
}

void NFBluePrintView::CreateExecuter()
{
	if (bCreatingExecuter)
	{
		auto currentObject = m_pBluePrintModule->FindBaseNode(mCurrentObjectID);
		if (currentObject)
		{
			if (currentObject->blueprintType == NFBlueprintType::JUDGEMENT
				|| currentObject->blueprintType == NFBlueprintType::EXECUTER)
			{
				ImGui::OpenPopup("Creating Executer");
				ImGui::SetNextWindowSize(ImVec2(230, 150));

				if (ImGui::BeginPopupModal("Creating Executer"))
				{
					static char str0[128] = "Hello, Executer!";
					ImGui::InputText("Executer Name", str0, IM_ARRAYSIZE(str0));

					ImGui::Separator();

					ImGui::Text("All those beautiful files will be deleted.\nThis operation cannot be undone!\n\n");

					ImGui::Separator();

					if (ImGui::Button("Cancel", ImVec2(100, 30)))
					{
						bCreatingExecuter = false;
						ImGui::CloseCurrentPopup();
					}

					ImGui::SameLine();

					if (ImGui::Button("OK", ImVec2(100, 30)))
					{
						if (currentObject->blueprintType == NFBlueprintType::JUDGEMENT)
						{
							//m_pBluePrintModule->AddExecuterForJudgement(mCurrentObjectID, m_pKernelModule->CreateGUID(), str0);
						}
						else if (currentObject->blueprintType == NFBlueprintType::EXECUTER)
						{
							m_pBluePrintModule->AddExecuterForExecuter(mCurrentObjectID, m_pKernelModule->CreateGUID(), str0);
						}

						bCreatingExecuter = false;
						ImGui::CloseCurrentPopup();
					}

					ImGui::EndPopup();
				}
			}
			else
			{
				bCreatingExecuter = false;
			}
		}
		else
		{
			bCreatingExecuter = false;
		}
	}
}

void NFBluePrintView::CreateVariable()
{
	if (bCreatingVariable)
	{
		auto currentObject = m_pBluePrintModule->FindBaseNode(mCurrentObjectID);
		if (currentObject)
		{
			ImGui::OpenPopup("Creating Variable");
			ImGui::SetNextWindowSize(ImVec2(230, 150));

			if (ImGui::BeginPopupModal("Creating Variable"))
			{
				static char str0[128] = "Hello, Variable!";
				ImGui::InputText("Variable Name", str0, IM_ARRAYSIZE(str0));

				ImGui::Separator();

				ImGui::Text("All those beautiful files will be deleted.\nThis operation cannot be undone!\n\n");

				ImGui::Separator();

				if (ImGui::Button("Cancel", ImVec2(100, 30)))
				{
					bCreatingVariable = false;
					ImGui::CloseCurrentPopup();
				}

				ImGui::SameLine();

				if (ImGui::Button("OK", ImVec2(100, 30)))
				{
					
					m_pBluePrintModule->AddVariableForLogicBlock(currentObject->logicBlockId, m_pKernelModule->CreateGUID(), str0);

					bCreatingVariable = false;
					ImGui::CloseCurrentPopup();
				}

				ImGui::EndPopup();
			}
		}
		else
		{
			bCreatingVariable = false;
		}
	}
}

void NFBluePrintView::CreateComparator()
{
	if (bCreatingComparator)
	{
		auto currentObject = m_pBluePrintModule->FindBaseNode(mCurrentObjectID);
		if (currentObject)
		{
			if (currentObject->blueprintType == NFBlueprintType::JUDGEMENT)
			{
				ImGui::OpenPopup("Creating Comparator");
				ImGui::SetNextWindowSize(ImVec2(230, 150));

				if (ImGui::BeginPopupModal("Creating Comparator"))
				{
					static char str0[128] = "Hello, Comparator!";
					ImGui::InputText("Comparator Name", str0, IM_ARRAYSIZE(str0));

					ImGui::Separator();

					ImGui::Text("All those beautiful files will be deleted.\nThis operation cannot be undone!\n\n");

					ImGui::Separator();

					if (ImGui::Button("Cancel", ImVec2(100, 30)))
					{
						bCreatingComparator = false;
						ImGui::CloseCurrentPopup();
					}

					ImGui::SameLine();

					if (ImGui::Button("OK", ImVec2(100, 30)))
					{
						auto judgement = std::dynamic_pointer_cast<NFJudgement>(currentObject);

						auto compator = NF_SHARE_PTR<NFComparator>(NF_NEW NFComparator());
						judgement->comparators.push_back(compator);

						bCreatingComparator = false;
						ImGui::CloseCurrentPopup();
					}

					ImGui::EndPopup();
				}
			}
         else
         {
            bCreatingComparator = false;
         }
		}
      else
      {
         bCreatingComparator = false;
      }
	}
}