/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.2.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
/*
 * ============================================================================
 *
 * FilesPane.cpp
 * GUI component for N64 ROM internal files screen
 *
 * From seq64 - Sequenced music editor for first-party N64 games
 * Copyright (C) 2014-2017 Sauraen
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * ============================================================================
*/

#include "MainComponent.h"
#include "BankFile.h"
#include "SeqFile.h"
//[/Headers]

#include "FilesPane.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
FilesPane::FilesPane (SEQ64& seq64_)
    : seq64(seq64_)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (groupComponent = new GroupComponent ("new group",
                                                            TRANS("Master File Table")));

    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("Address:")));
    label->setFont (Font (15.00f, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (txtFTAddr = new TextEditor ("new text editor"));
    txtFTAddr->setMultiLine (false);
    txtFTAddr->setReturnKeyStartsNewLine (false);
    txtFTAddr->setReadOnly (false);
    txtFTAddr->setScrollbarsShown (true);
    txtFTAddr->setCaretVisible (true);
    txtFTAddr->setPopupMenuEnabled (true);
    txtFTAddr->setText (String::empty);

    addAndMakeVisible (label2 = new Label ("new label",
                                           TRANS("Name:")));
    label2->setFont (Font (15.00f, Font::plain));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (txtFileName = new TextEditor ("new text editor"));
    txtFileName->setMultiLine (false);
    txtFileName->setReturnKeyStartsNewLine (false);
    txtFileName->setReadOnly (false);
    txtFileName->setScrollbarsShown (true);
    txtFileName->setCaretVisible (true);
    txtFileName->setPopupMenuEnabled (true);
    txtFileName->setText (String::empty);

    addAndMakeVisible (label3 = new Label ("new label",
                                           TRANS("Type:")));
    label3->setFont (Font (15.00f, Font::plain));
    label3->setJustificationType (Justification::centredLeft);
    label3->setEditable (false, false, false);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (cbxFileType = new ComboBox ("new combo box"));
    cbxFileType->setEditableText (false);
    cbxFileType->setJustificationType (Justification::centredLeft);
    cbxFileType->setTextWhenNothingSelected (String::empty);
    cbxFileType->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    cbxFileType->addItem (TRANS("Unknown"), 1);
    cbxFileType->addItem (TRANS("ROM Header"), 2);
    cbxFileType->addItem (TRANS("Boot Code"), 3);
    cbxFileType->addItem (TRANS("Master File Table"), 4);
    cbxFileType->addItem (TRANS("Audiobank"), 5);
    cbxFileType->addItem (TRANS("Audioseq"), 6);
    cbxFileType->addItem (TRANS("Audiotable"), 7);
    cbxFileType->addItem (TRANS("Code"), 8);
    cbxFileType->addItem (TRANS("Texture"), 9);
    cbxFileType->addItem (TRANS("Shared Assets"), 10);
    cbxFileType->addItem (TRANS("Text Data"), 11);
    cbxFileType->addItem (TRANS("Actor"), 12);
    cbxFileType->addItem (TRANS("Object"), 13);
    cbxFileType->addItem (TRANS("Scene"), 14);
    cbxFileType->addItem (TRANS("Room"), 15);
    cbxFileType->addItem (TRANS("Other"), 16);
    cbxFileType->addListener (this);

    addAndMakeVisible (label4 = new Label ("new label",
                                           TRANS("[Address information]")));
    label4->setFont (Font (15.00f, Font::plain));
    label4->setJustificationType (Justification::centredLeft);
    label4->setEditable (false, false, false);
    label4->setColour (TextEditor::textColourId, Colours::black);
    label4->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (groupComponent2 = new GroupComponent ("new group",
                                                             TRANS("Known Files")));

    addAndMakeVisible (btnKFileAdd = new TextButton ("new button"));
    btnKFileAdd->setButtonText (TRANS("Add"));
    btnKFileAdd->setConnectedEdges (Button::ConnectedOnRight);
    btnKFileAdd->addListener (this);

    addAndMakeVisible (btnKFileDel = new TextButton ("new button"));
    btnKFileDel->setButtonText (TRANS("Del"));
    btnKFileDel->setConnectedEdges (Button::ConnectedOnLeft);
    btnKFileDel->addListener (this);

    addAndMakeVisible (label5 = new Label ("new label",
                                           TRANS("Type:")));
    label5->setFont (Font (15.00f, Font::plain));
    label5->setJustificationType (Justification::centredLeft);
    label5->setEditable (false, false, false);
    label5->setColour (TextEditor::textColourId, Colours::black);
    label5->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (cbxKFileType = new ComboBox ("new combo box"));
    cbxKFileType->setEditableText (false);
    cbxKFileType->setJustificationType (Justification::centredLeft);
    cbxKFileType->setTextWhenNothingSelected (String::empty);
    cbxKFileType->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    cbxKFileType->addItem (TRANS("Unsupported"), 1);
    cbxKFileType->addItem (TRANS("Audiobank"), 2);
    cbxKFileType->addItem (TRANS("Audioseq"), 3);
    cbxKFileType->addItem (TRANS("Audiotable"), 4);
    cbxKFileType->addItem (TRANS("Audiobank Index"), 5);
    cbxKFileType->addItem (TRANS("Audioseq Index"), 6);
    cbxKFileType->addItem (TRANS("Sample Set Index"), 7);
    cbxKFileType->addItem (TRANS("Instrument Set Index"), 8);
    cbxKFileType->addListener (this);

    addAndMakeVisible (label6 = new Label ("new label",
                                           TRANS("Address:")));
    label6->setFont (Font (15.00f, Font::plain));
    label6->setJustificationType (Justification::centredLeft);
    label6->setEditable (false, false, false);
    label6->setColour (TextEditor::textColourId, Colours::black);
    label6->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (txtKFileAddr = new TextEditor ("new text editor"));
    txtKFileAddr->setMultiLine (false);
    txtKFileAddr->setReturnKeyStartsNewLine (false);
    txtKFileAddr->setReadOnly (false);
    txtKFileAddr->setScrollbarsShown (true);
    txtKFileAddr->setCaretVisible (true);
    txtKFileAddr->setPopupMenuEnabled (true);
    txtKFileAddr->setText (String::empty);

    addAndMakeVisible (label7 = new Label ("new label",
                                           TRANS("Length:")));
    label7->setFont (Font (15.00f, Font::plain));
    label7->setJustificationType (Justification::centredLeft);
    label7->setEditable (false, false, false);
    label7->setColour (TextEditor::textColourId, Colours::black);
    label7->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (txtKFileLength = new TextEditor ("new text editor"));
    txtKFileLength->setMultiLine (false);
    txtKFileLength->setReturnKeyStartsNewLine (false);
    txtKFileLength->setReadOnly (false);
    txtKFileLength->setScrollbarsShown (true);
    txtKFileLength->setCaretVisible (true);
    txtKFileLength->setPopupMenuEnabled (true);
    txtKFileLength->setText (String::empty);

    addAndMakeVisible (grpIndex = new GroupComponent ("new group",
                                                      TRANS("Index")));

    addAndMakeVisible (lblIndexProps = new Label ("new label",
                                                  TRANS("[Index length, address, etc.]")));
    lblIndexProps->setFont (Font (15.00f, Font::plain));
    lblIndexProps->setJustificationType (Justification::centredLeft);
    lblIndexProps->setEditable (false, false, false);
    lblIndexProps->setColour (TextEditor::textColourId, Colours::black);
    lblIndexProps->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label11 = new Label ("new label",
                                            TRANS("Name:")));
    label11->setFont (Font (15.00f, Font::plain));
    label11->setJustificationType (Justification::centredLeft);
    label11->setEditable (false, false, false);
    label11->setColour (TextEditor::textColourId, Colours::black);
    label11->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (txtIEntryName = new TextEditor ("new text editor"));
    txtIEntryName->setMultiLine (false);
    txtIEntryName->setReturnKeyStartsNewLine (false);
    txtIEntryName->setReadOnly (false);
    txtIEntryName->setScrollbarsShown (true);
    txtIEntryName->setCaretVisible (true);
    txtIEntryName->setPopupMenuEnabled (true);
    txtIEntryName->setText (String::empty);

    addAndMakeVisible (lblIEntryData = new Label ("new label",
                                                  TRANS("[Entry data]")));
    lblIEntryData->setFont (Font (15.00f, Font::plain));
    lblIEntryData->setJustificationType (Justification::centredLeft);
    lblIEntryData->setEditable (false, false, false);
    lblIEntryData->setColour (TextEditor::textColourId, Colours::black);
    lblIEntryData->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (btnLoadEntry = new TextButton ("new button"));
    btnLoadEntry->setButtonText (TRANS("Load Entry"));
    btnLoadEntry->setConnectedEdges (Button::ConnectedOnBottom);
    btnLoadEntry->addListener (this);

    addAndMakeVisible (btnSaveEntry = new TextButton ("new button"));
    btnSaveEntry->setButtonText (TRANS("Save Entry"));
    btnSaveEntry->setConnectedEdges (Button::ConnectedOnTop);
    btnSaveEntry->addListener (this);

    addAndMakeVisible (groupComponent4 = new GroupComponent ("new group",
                                                             TRANS("Index Format")));

    addAndMakeVisible (optIndexType1 = new ToggleButton ("new toggle button"));
    optIndexType1->setButtonText (TRANS("Word hdr; [addr, length] (SM64, MK64)"));
    optIndexType1->setRadioGroupId (1);
    optIndexType1->addListener (this);
    optIndexType1->setToggleState (true, dontSendNotification);

    addAndMakeVisible (optIndexType2 = new ToggleButton ("new toggle button"));
    optIndexType2->setButtonText (TRANS("4-word hdr; [addr, length, 2 data] (Zelda, Yoshi)"));
    optIndexType2->setRadioGroupId (1);
    optIndexType2->addListener (this);

    addAndMakeVisible (lblInstSet = new Label ("new label",
                                               TRANS("Instrument sets:")));
    lblInstSet->setFont (Font (15.00f, Font::plain));
    lblInstSet->setJustificationType (Justification::centredLeft);
    lblInstSet->setEditable (false, false, false);
    lblInstSet->setColour (TextEditor::textColourId, Colours::black);
    lblInstSet->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label10 = new Label ("new label",
                                            TRANS("Set:")));
    label10->setFont (Font (15.00f, Font::plain));
    label10->setJustificationType (Justification::centredLeft);
    label10->setEditable (false, false, false);
    label10->setColour (TextEditor::textColourId, Colours::black);
    label10->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (cbxInstSet1 = new ComboBox ("new combo box"));
    cbxInstSet1->setEditableText (false);
    cbxInstSet1->setJustificationType (Justification::centredLeft);
    cbxInstSet1->setTextWhenNothingSelected (String::empty);
    cbxInstSet1->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    cbxInstSet1->addListener (this);


    //[UserPreSize]
    lsmFileTable = new TextListModel();
    lsmFileTable->setListener(this);

    addAndMakeVisible(lstFileTable = new ListBox("FileTable", lsmFileTable));
    lstFileTable->setMultipleSelectionEnabled(false);
    lstFileTable->setRowHeight(16);
    lstFileTable->setOutlineThickness(1);
    lstFileTable->setColour(ListBox::outlineColourId, Colours::lightgrey);

    lsmKFiles = new TextListModel();
    lsmKFiles->setListener(this);

    addAndMakeVisible(lstKFiles = new ListBox("KFiles", lsmKFiles));
    lstKFiles->setMultipleSelectionEnabled(false);
    lstKFiles->setRowHeight(16);
    lstKFiles->setOutlineThickness(1);
    lstKFiles->setColour(ListBox::outlineColourId, Colours::lightgrey);

    lsmIndex = new TextListModel();
    lsmIndex->setListener(this);

    addAndMakeVisible(lstIndex = new ListBox("Index", lsmIndex));
    lstIndex->setMultipleSelectionEnabled(false);
    lstIndex->setRowHeight(16);
    lstIndex->setOutlineThickness(1);
    lstIndex->setColour(ListBox::outlineColourId, Colours::lightgrey);

    lsmInstSets = new TextListModel();
    lsmInstSets->setListener(this);

    addAndMakeVisible(lstInstSets = new ListBox("InstSets", lsmInstSets));
    lstInstSets->setMultipleSelectionEnabled(false);
    lstInstSets->setRowHeight(16);
    lstInstSets->setOutlineThickness(1);
    lstInstSets->setColour(ListBox::outlineColourId, Colours::lightgrey);

    txtFTAddr->addListener(this);
    txtFileName->addListener(this);
    txtKFileAddr->addListener(this);
    txtKFileLength->addListener(this);
    txtIEntryName->addListener(this);

    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    ftaddr = 0;
    ftend = 0;
    dataaddr = -1;
    abi_addr = -1;
    asi_addr = -1;
    ssi_addr = -1;
    isi_addr = -1;
    abi_count = -1;
    asi_count = -1;
    ssi_count = -1;
    seq_lastbank = -1;

    romDescLoaded();
    //[/Constructor]
}

FilesPane::~FilesPane()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    groupComponent = nullptr;
    label = nullptr;
    txtFTAddr = nullptr;
    label2 = nullptr;
    txtFileName = nullptr;
    label3 = nullptr;
    cbxFileType = nullptr;
    label4 = nullptr;
    groupComponent2 = nullptr;
    btnKFileAdd = nullptr;
    btnKFileDel = nullptr;
    label5 = nullptr;
    cbxKFileType = nullptr;
    label6 = nullptr;
    txtKFileAddr = nullptr;
    label7 = nullptr;
    txtKFileLength = nullptr;
    grpIndex = nullptr;
    lblIndexProps = nullptr;
    label11 = nullptr;
    txtIEntryName = nullptr;
    lblIEntryData = nullptr;
    btnLoadEntry = nullptr;
    btnSaveEntry = nullptr;
    groupComponent4 = nullptr;
    optIndexType1 = nullptr;
    optIndexType2 = nullptr;
    lblInstSet = nullptr;
    label10 = nullptr;
    cbxInstSet1 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void FilesPane::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void FilesPane::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    groupComponent->setBounds (0, 0, 336, 448);
    label->setBounds (8, 16, 72, 24);
    txtFTAddr->setBounds (80, 16, 80, 24);
    label2->setBounds (8, 392, 56, 24);
    txtFileName->setBounds (64, 392, 264, 24);
    label3->setBounds (8, 416, 56, 24);
    cbxFileType->setBounds (64, 416, 264, 24);
    label4->setBounds (8, 368, 320, 24);
    groupComponent2->setBounds (0, 448, 336, 264);
    btnKFileAdd->setBounds (8, 624, 40, 24);
    btnKFileDel->setBounds (48, 624, 40, 24);
    label5->setBounds (96, 624, 47, 24);
    cbxKFileType->setBounds (144, 624, 184, 24);
    label6->setBounds (176, 656, 72, 24);
    txtKFileAddr->setBounds (248, 656, 80, 24);
    label7->setBounds (176, 680, 72, 24);
    txtKFileLength->setBounds (248, 680, 80, 24);
    grpIndex->setBounds (336, 0, 424, 712);
    lblIndexProps->setBounds (344, 88, 408, 24);
    label11->setBounds (344, 472, 56, 24);
    txtIEntryName->setBounds (400, 472, 352, 24);
    lblIEntryData->setBounds (344, 448, 408, 24);
    btnLoadEntry->setBounds (344, 504, 136, 24);
    btnSaveEntry->setBounds (344, 528, 136, 24);
    groupComponent4->setBounds (344, 16, 408, 72);
    optIndexType1->setBounds (352, 32, 392, 24);
    optIndexType2->setBounds (352, 56, 392, 24);
    lblInstSet->setBounds (344, 560, 408, 24);
    label10->setBounds (344, 680, 40, 24);
    cbxInstSet1->setBounds (384, 680, 368, 24);
    //[UserResized] Add your own custom resize handling here..
    lstFileTable->setBounds (8, 48, 320, 320);
    lstKFiles->setBounds (8, 464, 320, 152);
    lstIndex->setBounds (344, 120, 408, 320);
    lstInstSets->setBounds (344, 584, 408, 88);
    //[/UserResized]
}

void FilesPane::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == cbxFileType)
    {
        //[UserComboBoxCode_cbxFileType] -- add your combo box handling code here..
        int findex = lstFileTable->getLastRowSelected();
        if(findex < 0) return;
        if(ftaddr == 0) return;
        String type = cbxFileType->getText();
        //See if we are removing a known file
        ValueTree kfile = kfilelistnode.getChildWithProperty("ftindex", findex);
        if(kfile.isValid()){
            changedIndexAddress(type, -1);
            kfilelistnode.removeChild(kfile, nullptr);
            fillKFiles();
        }
        if(isKnownFileType(type)){
            //See if we already know about this type of file
            kfile = kfilelistnode.getChildWithProperty(Identifier("type"), type);
            if(kfile.isValid()){
                SEQ64::say(type + " file already exists!");
                cbxFileType->setText("Unknown");
                return;
            }
            //Set up this known file
            kfile = ValueTree(Identifier("knownfile"));
            kfile.setProperty(Identifier("type"), type, nullptr);
            kfile.setProperty(Identifier("from_ft"), true, nullptr);
            kfile.setProperty(Identifier("ftindex"), findex, nullptr);
            uint32 a = ftaddr + 0x10*findex;
            uint32 file_addr = (int)seq64.rom.readWord(a);
            kfile.setProperty(Identifier("address"), (int)file_addr, nullptr);
            kfile.setProperty(Identifier("length"), (int)(seq64.rom.readWord(a+4) - seq64.rom.readWord(a)), nullptr);
            changedIndexAddress(type, file_addr);
            kfilelistnode.addChild(kfile, kfilelistnode.getNumChildren(), nullptr);
            fillKFiles();
            lstKFiles->selectRow(lsmKFiles->getNumRows() - 1);
        }
        ValueTree file = filelistnode.getChildWithProperty(Identifier("index"), findex);
        if(!file.isValid()){
            file = ValueTree(Identifier("file"));
            file.setProperty(Identifier("index"), findex, nullptr);
            filelistnode.addChild(file, filelistnode.getNumChildren(), nullptr);
        }
        file.setProperty(Identifier("type"), type, nullptr);
        //[/UserComboBoxCode_cbxFileType]
    }
    else if (comboBoxThatHasChanged == cbxKFileType)
    {
        //[UserComboBoxCode_cbxKFileType] -- add your combo box handling code here..
        if(!selkfile.isValid()) return;
        if((bool)selkfile.getProperty("from_ft", false)){
            //Prevent you from changing it
            fillKFileParams();
            return;
        }
        String type = cbxKFileType->getText();
        //Check for existing file of this type
        if(type != "Unsupported"){
            ValueTree kfile = kfilelistnode.getChildWithProperty(Identifier("type"), type);
            if(kfile.isValid() && kfile != selkfile){
                SEQ64::say(type + " file already exists!");
                cbxKFileType->setText("Unsupported");
                type = "Unsupported";
            }
        }
        //Remove old index address, insert new
        String oldtype = selkfile.getProperty("type");
        changedIndexAddress(type, -1);
        uint32 addr = (int)selkfile.getProperty("address");
        changedIndexAddress(type, addr);
        selkfile.setProperty("type", type, nullptr);
        //Refresh display
        int idx = lstKFiles->getLastRowSelected();
        lsmKFiles->set(idx, cbxKFileType->getText());
        lstKFiles->repaintRow(idx);
        //[/UserComboBoxCode_cbxKFileType]
    }
    else if (comboBoxThatHasChanged == cbxInstSet1)
    {
        //[UserComboBoxCode_cbxInstSet1] -- add your combo box handling code here..
        if(!selindex.isValid()) return;
        if(selindex.getProperty("type", "Unsupported").toString() != "Audioseq Index") return;
        if(ientryidx < 0) return;
        if(isi_addr < 0) return;
        int idx = cbxInstSet1->getSelectedItemIndex();
        int row = lstInstSets->getLastRowSelected();
        if(idx < 0 || row < 0) return;
        uint16 ptr = seq64.rom.readHalfWord(isi_addr + (ientryidx << 1));
        seq64.rom.writeByte(isi_addr + ptr + row + 1, idx & 0x000000FF);
        lsmInstSets->set(row, cbxInstSet1->getText());
        lstInstSets->repaintRow(row);
        //[/UserComboBoxCode_cbxInstSet1]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void FilesPane::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == btnKFileAdd)
    {
        //[UserButtonCode_btnKFileAdd] -- add your button handler code here..
        ValueTree kfile(Identifier("knownfile"));
        kfile.setProperty(Identifier("type"), "Unsupported", nullptr);
        kfile.setProperty(Identifier("from_ft"), false, nullptr);
        kfile.setProperty(Identifier("address"), 0, nullptr);
        kfile.setProperty(Identifier("length"), 0, nullptr);
        kfilelistnode.addChild(kfile, kfilelistnode.getNumChildren(), nullptr);
        fillKFiles();
        lstKFiles->selectRow(lsmKFiles->getNumRows() - 1);
        //[/UserButtonCode_btnKFileAdd]
    }
    else if (buttonThatWasClicked == btnKFileDel)
    {
        //[UserButtonCode_btnKFileDel] -- add your button handler code here..
        if(!selkfile.isValid()) return;
        if((bool)selkfile.getProperty("from_ft", false)){
            SEQ64::say("From file table, can't delete!");
            return;
        }
        //Remove old index address
        String oldtype = selkfile.getProperty("type");
        changedIndexAddress(oldtype, -1);
        //Remove kfile
        kfilelistnode.removeChild(selkfile, nullptr);
        selkfile = ValueTree();
        fillKFiles();
        lstKFiles->selectRow(-1);
        //[/UserButtonCode_btnKFileDel]
    }
    else if (buttonThatWasClicked == btnLoadEntry)
    {
        //[UserButtonCode_btnLoadEntry] -- add your button handler code here..
        if(!idxlistnode.isValid()) return;
        if(ientryidx < 0) return;
        if(dataaddr < 0) return;
        if(idxlistnode.hasType("audiobankidx")){
            if(&*seq64.bank != nullptr){
                if(!NativeMessageBox::showOkCancelBox(AlertWindow::WarningIcon,
                        "Overwrite?", "A bank is already loaded, overwrite it?", nullptr, nullptr)) return;
            }
            seq64.bank = new BankFile(seq64.romdesc);
            seq64.bank->load(seq64.rom, ientryidx);
            //TODO debug only
            File f = File::getSpecialLocation(File::userHomeDirectory).getChildFile("audiobank.log");
            f.replaceWithText(seq64.bank->d.toXmlString());
            //^^end debug only
            seq64.maincomponent->onBankLoaded();
        }else if(idxlistnode.hasType("audioseqidx")){
            if(&*seq64.seq != nullptr){
                if(!NativeMessageBox::showOkCancelBox(AlertWindow::WarningIcon,
                        "Overwrite?", "A sequence is already loaded, overwrite it?", nullptr, nullptr)) return;
            }
            seq64.seq = new SeqFile(seq64.romdesc);
            seq64.seq->load(seq64.rom, ientryidx);
            seq64.seq->name = ROM::hex((uint8)ientryidx) + " " + txtIEntryName->getText();
            seq64.maincomponent->onSeqLoaded();
        }else{
            NativeMessageBox::showMessageBoxAsync (AlertWindow::InfoIcon, "Load Entry",
                    "Loading an entry from " + idxlistnode.getType().toString() + " not supported");
        }
        //[/UserButtonCode_btnLoadEntry]
    }
    else if (buttonThatWasClicked == btnSaveEntry)
    {
        //[UserButtonCode_btnSaveEntry] -- add your button handler code here..
        if(!idxlistnode.isValid()) return;
        if(ientryidx < 0) return;
        if(dataaddr < 0) return;
        if(idxlistnode.hasType("audiobankidx")){
            if(&*seq64.bank == nullptr){
                return;
            }
            if(!NativeMessageBox::showOkCancelBox(AlertWindow::WarningIcon,
                    "Overwrite?", "Replace bank " + String(ientryidx) + " with the currently loaded one?"
                    + "\n(This does not save the ROM to disk.)", nullptr, nullptr)) return;
            seq64.bank->save(seq64.rom, ientryidx);
            fillIndex();
        }else if(idxlistnode.hasType("audioseqidx")){
            if(&*seq64.seq == nullptr){
                return;
            }
            uint32 seqaddr, length;
            if((int)seq64.romdesc.getProperty("indextype", 1) == 2){
                seqaddr = dataaddr + seq64.rom.readWord(indexaddr + (16*ientryidx) + 16);
                length = seq64.rom.readWord(indexaddr + (16*ientryidx) + 20);
            }else{
                seqaddr = dataaddr + seq64.rom.readWord(indexaddr + (8*ientryidx) + 4);
                length = seq64.rom.readWord(indexaddr + (8*ientryidx) + 8);
            }
            uint32 loadedseqlength = seq64.seq->getLength();
            if(loadedseqlength > length){
                NativeMessageBox::showMessageBoxAsync (AlertWindow::InfoIcon, "Save Entry",
                        "Currently, saving larger sequence (" + ROM::hex(loadedseqlength, 4)
                        + " bytes)\ninto smaller space (" + ROM::hex(length, 4) + " bytes) is not supported.");
                return;
            }
            if(!NativeMessageBox::showOkCancelBox(AlertWindow::WarningIcon,
                    "Overwrite?", "Replace the sequence @" + ROM::hex(seqaddr) + " (" + ROM::hex(length, 4)
                    + " bytes)\nwith the currently loaded one (" + ROM::hex(loadedseqlength, 4) + " bytes)?"
                    + "\n(This does not save the ROM to disk.)", nullptr, nullptr)) return;
            seq64.seq->saveToROM(seq64.rom, seqaddr);
        }else{
            NativeMessageBox::showMessageBoxAsync (AlertWindow::InfoIcon, "Save Entry",
                    "Saving an entry to " + idxlistnode.getType().toString() + " not supported");
        }
        //[/UserButtonCode_btnSaveEntry]
    }
    else if (buttonThatWasClicked == optIndexType1)
    {
        //[UserButtonCode_optIndexType1] -- add your button handler code here..
        seq64.romdesc.setProperty("indextype", 1, nullptr);
        //[/UserButtonCode_optIndexType1]
    }
    else if (buttonThatWasClicked == optIndexType2)
    {
        //[UserButtonCode_optIndexType2] -- add your button handler code here..
        seq64.romdesc.setProperty("indextype", 2, nullptr);
        //[/UserButtonCode_optIndexType2]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void FilesPane::rowSelected(TextListModel* parent, int row){
    if(parent == &*lsmFileTable){
        ValueTree file = filelistnode.getChildWithProperty(Identifier("index"), row);
        if(file.isValid()){
            txtFileName->setText(file.getProperty("name", ""));
            cbxFileType->setText(file.getProperty("type", "Unknown"));
        }else{
            txtFileName->setText("");
            cbxFileType->setText("Unknown");
        }
    }else if(parent == &*lsmKFiles){
        selkfile = kfilelistnode.getChild(row);
        fillKFileParams();
        String type = selkfile.getProperty("type", "Unsupported");
        if(type == "Audiobank Index" || type == "Audioseq Index" || type == "Sample Set Index"){
            selindex = selkfile;
        }else{
            selindex = ValueTree();
        }
        fillIndex();
    }else if(parent == &*lsmIndex){
        ientryidx = row;
        fillIEntryParams();
    }else if(parent == &*lsmInstSets){
        if(isi_addr < 0) return;
        if(abi_addr < 0) return;
        if(abi_count < 0 || abi_count >= 0x100) return;
        uint16 ptr = seq64.rom.readHalfWord(isi_addr + (ientryidx << 1));
        uint8 b = seq64.rom.readByte(isi_addr + ptr + row + 1);
        if(b >= abi_count){
            cbxInstSet1->setText("Error: value " + ROM::hex(b) + "!", dontSendNotification);
        }else{
            cbxInstSet1->setSelectedItemIndex(b, dontSendNotification);
        }
    }
}
void FilesPane::textEditorTextChanged(TextEditor& editorThatWasChanged){
    String text = editorThatWasChanged.getText();
    //int decval = text.getIntValue();
    int hexval = text.getHexValue32();
    bool turnRed = false;
    if(&editorThatWasChanged == &*txtFTAddr){
        ftaddr = hexval;
        if(seq64.rom.getSize() == 0 || seq64.rom.getSize() <= ftaddr + 16){
            ftaddr = 0;
            turnRed = true;
        }else if(seq64.rom.readWord(ftaddr + 0x20) != ftaddr){
            SEQ64::say("Data at " + ROM::hex(ftaddr) + " is not a file table");
            ftaddr = 0;
            turnRed = true;
        }else{
            ftend = seq64.rom.readWord(ftaddr + 0x24);
            seq64.romdesc.setProperty("ftaddr", (int)ftaddr, nullptr);
            fillFileTable();
            turnRed = false;
        }
    }else if(&editorThatWasChanged == &*txtFileName){
        int findex = lstFileTable->getLastRowSelected();
        if(findex < 0) return;
        if(ftaddr == 0) return;
        ValueTree file = filelistnode.getChildWithProperty(Identifier("index"), findex);
        if(!file.isValid()){
            file = ValueTree(Identifier("file"));
            file.setProperty(Identifier("index"), findex, nullptr);
            filelistnode.addChild(file, filelistnode.getNumChildren(), nullptr);
        }
        file.setProperty(Identifier("name"), text, nullptr);
        uint32 a = ftaddr + 0x10*findex;
        lsmFileTable->set(findex, getFileDescription(a, findex));
        lstFileTable->repaintRow(findex);
    }else if(&editorThatWasChanged == &*txtKFileAddr){
        if(!selkfile.isValid()) return;
        if((bool)selkfile.getProperty("from_ft", false)){
            //Prevent you from changing it
            fillKFileParams();
            return;
        }
        selkfile.setProperty("address", hexval, nullptr);
        if(hexval <= 0) turnRed = true;
        if(selindex.isValid()) fillIndex();
    }else if(&editorThatWasChanged == &*txtKFileLength){
        if(!selkfile.isValid()) return;
        if((bool)selkfile.getProperty("from_ft", false)){
            //Prevent you from changing it
            fillKFileParams();
            return;
        }
        selkfile.setProperty("length", hexval, nullptr);
        if(hexval <= 0) turnRed = true;
    }else if(&editorThatWasChanged == &*txtIEntryName){
        if(!idxlistnode.isValid()) return;
        if(ientryidx < 0) return;
        ValueTree entry = idxlistnode.getChildWithProperty(Identifier("index"), ientryidx);
        if(!entry.isValid()){
            if(text == "") return;
            entry = ValueTree(Identifier("indexentry"));
            entry.setProperty("index", ientryidx, nullptr);
            idxlistnode.addChild(entry, idxlistnode.getNumChildren(), nullptr);
        }
        entry.setProperty("name", text, nullptr);
        lsmIndex->set(ientryidx, getIEntryDescription(ientryidx));
        lstIndex->repaintRow(ientryidx);
    }
    if(turnRed){
        editorThatWasChanged.setColour(TextEditor::backgroundColourId, Colours::red);
    }else{
        editorThatWasChanged.setColour(TextEditor::backgroundColourId, Colours::white);
    }
}

String FilesPane::getFileDescription(uint32 a, int i){
    String desc;
    ValueTree file = filelistnode.getChildWithProperty(Identifier("index"), i);
    if(file.isValid()){
        desc = file.getProperty(Identifier("name"));
    }else{
        desc = "?";
    }
    desc += ": @" + ROM::hex(seq64.rom.readWord(a)) + " to " + ROM::hex(seq64.rom.readWord(a+4));
    if(seq64.rom.readWord(a+12) != 0){
        desc += " (*)";
    }
    return desc;
}

void FilesPane::fillFileTable(){
    lsmFileTable->clear();
    lstFileTable->updateContent();
    if(ftaddr == 0 || ftend <= ftaddr || ftend - ftaddr >= 0x10000){
        lstFileTable->updateContent();
        return;
    }
    //Show table
    uint32 a;
    int i;
    for(a=ftaddr, i=0; a<ftend; a += 0x10, i++){
        lsmFileTable->add(getFileDescription(a, i));
        if(i > 10000){
            SEQ64::say("More than 10,000 files, exiting!");
            a = ftend + 1;
            break;
        }
    }
    lstFileTable->updateContent();
}

void FilesPane::fillKFiles(){
    lsmKFiles->clear();
    for(int c=0; c<kfilelistnode.getNumChildren(); c++){
        lsmKFiles->add(kfilelistnode.getChild(c).getProperty("type", "Unsupported"));
    }
    lstKFiles->updateContent();
}

void FilesPane::fillKFileParams(){
    if(selkfile.isValid()){
        cbxKFileType->setText(selkfile.getProperty("type", "Unsupported"));
        txtKFileAddr->setText(ROM::hex((uint32)(int)selkfile.getProperty("address", 0)));
        txtKFileLength->setText(ROM::hex((uint32)(int)selkfile.getProperty("length", 0)));
    }else{
        cbxKFileType->setText("");
        txtKFileAddr->setText("");
        txtKFileLength->setText("");
    }
}

String FilesPane::getIEntryDescription(int i){
    if(!idxlistnode.isValid()) return "";
    if(seq64.rom.getSize() == 0) return "";
    ValueTree entry = idxlistnode.getChildWithProperty("index", i);
    String ret = ROM::hex((uint8)i) + " ";
    if(entry.isValid()){
        ret += entry.getProperty("name", "[Unnamed]").toString();
        ret += ": ";
    }
    if((int)seq64.romdesc.getProperty("indextype", 1) == 2){
        ret += "@" + ROM::hex(seq64.rom.readWord(indexaddr + (16*i) + 16), 6);
        ret += ", len " + ROM::hex(seq64.rom.readWord(indexaddr + (16*i) + 20), 6);
    }else{
        ret += "@" + ROM::hex(seq64.rom.readWord(indexaddr + (8*i) + 4), 6);
        ret += ", len " + ROM::hex(seq64.rom.readWord(indexaddr + (8*i) + 8), 6);
    }
    return ret;
}

void FilesPane::fillIndex(){
    lsmInstSets->clear();
    lstInstSets->updateContent();
    lsmIndex->clear();
    lstIndex->updateContent();
    if(seq64.rom.getSize() == 0){
        lblIndexProps->setText("No ROM loaded", dontSendNotification);
        lstIndex->updateContent();
        return;
    }
    if(!selindex.isValid()){
        lblIndexProps->setText("No index file selected", dontSendNotification);
        lstIndex->updateContent();
        return;
    }
    String type = selindex.getProperty("type", "Unsupported");
    if(type == "Audiobank Index"){
        seldata = kfilelistnode.getChildWithProperty("type", "Audiobank");
        if(!seldata.isValid()){
            lblIndexProps->setText("No Audiobank file specified", dontSendNotification);
            lstIndex->updateContent();
            return;
        }
        dataaddr = (int)seldata.getProperty("address", -1);
        if(dataaddr < 0){
            SEQ64::say("Audiobank file has no address!");
            return;
        }
        idxlistnode = seq64.romdesc.getOrCreateChildWithName("audiobankidx", nullptr);
        btnLoadEntry->setButtonText("Load Bank");
        btnSaveEntry->setButtonText("Save Bank");
    }else if(type == "Audioseq Index"){
        seldata = kfilelistnode.getChildWithProperty("type", "Audioseq");
        if(!seldata.isValid()){
            lblIndexProps->setText("No Audioseq file specified", dontSendNotification);
            lstIndex->updateContent();
            return;
        }
        dataaddr = (int)seldata.getProperty("address", -1);
        if(dataaddr < 0){
            SEQ64::say("Audioseq file has no address!");
            return;
        }
        idxlistnode = seq64.romdesc.getOrCreateChildWithName("audioseqidx", nullptr);
        btnLoadEntry->setButtonText("Load Sequence");
        btnSaveEntry->setButtonText("Save Sequence");
    }else if(type == "Sample Set Index"){
        //No data associated
        idxlistnode = seq64.romdesc.getOrCreateChildWithName("samplesetidx", nullptr);
    }else{
        lblIndexProps->setText("File selected is not an index", dontSendNotification);
        lstIndex->updateContent();
        return;
    }
    grpIndex->setText(type);
    //
    indexaddr = (int)selindex.getProperty("address", 0);
    uint16 count;
    if((int)seq64.romdesc.getProperty("indextype", 1) == 2){
        count = seq64.rom.readHalfWord(indexaddr);
    }else{
        count = seq64.rom.readHalfWord(indexaddr+2);
    }
    if(count > 1000 || count <= 0){
        lblIndexProps->setText(String(count) + " entries, probably wrong", dontSendNotification);
        lstIndex->updateContent();
        return;
    }
    lblIndexProps->setText(String(count) + " entries", dontSendNotification);
    for(int i=0; i<count; i++){
        lsmIndex->add(getIEntryDescription(i));
    }
    lstIndex->updateContent();
    fillInstSetBoxes();
    if(type == "Audiobank Index"){
        seq64.maincomponent->onGotABI();
    }
}

void FilesPane::fillIEntryParams(){
    if(!selindex.isValid()){
        txtIEntryName->setText("");
        lblIEntryData->setText("[Entry data]", dontSendNotification);
        return;
    }
    String data;
    if((int)seq64.romdesc.getProperty("indextype", 1) == 2){
        data  = "@" + ROM::hex(seq64.rom.readWord(indexaddr + (16*ientryidx) + 16));
        data += ", len " + ROM::hex(seq64.rom.readWord(indexaddr + (16*ientryidx) + 20));
        data += ": " + ROM::hex(seq64.rom.readWord(indexaddr + (16*ientryidx) + 24));
        data += " " + ROM::hex(seq64.rom.readWord(indexaddr + (16*ientryidx) + 28));
    }else{
        data  = "@" + ROM::hex(seq64.rom.readWord(indexaddr + (8*ientryidx) + 4));
        data += ", len " + ROM::hex(seq64.rom.readWord(indexaddr + (8*ientryidx) + 8));
    }
    lblIEntryData->setText(data, dontSendNotification);
    ValueTree entry = idxlistnode.getChildWithProperty("index", ientryidx);
    if(entry.isValid()){
        txtIEntryName->setText(entry.getProperty("name", "[Unnamed]").toString());
    }else{
        txtIEntryName->setText("");
    }
    //Select instrument sets
    if(selindex.getProperty("type", "Unsupported").toString() != "Audioseq Index") return;
    if(isi_addr < 0) return;
    if(abi_addr < 0) return;
    if(abi_count < 0 || abi_count >= 0x100) return;
    uint16 ptr = seq64.rom.readHalfWord(isi_addr + (ientryidx << 1));
    uint32 a = isi_addr + ptr;
    int seq_isetcount = seq64.rom.readByte(a);
    a++;
    int sel_seqiset = lstInstSets->getLastRowSelected();
    //Make list
    lsmInstSets->clear();
    lstInstSets->updateContent();
    uint8 b;
    ValueTree abk_names = seq64.romdesc.getOrCreateChildWithName("audiobankidx", nullptr);
    String desc;
    ValueTree bank;
    for(int i=0; i<seq_isetcount; i++){
        b = seq64.rom.readByte(a);
        a++;
        desc = ROM::hex(b);
        bank = abk_names.getChildWithProperty("index", b);
        if(bank.isValid()){
            desc += ": " + bank.getProperty("name", "[Unnamed]").toString();
        }
        lsmInstSets->add(desc);
        seq_lastbank = b;
    }
    lstInstSets->updateContent();
    lstInstSets->selectRow(sel_seqiset);
}

void FilesPane::romDescLoaded(){
    filelistnode = seq64.romdesc.getOrCreateChildWithName("filelist", nullptr);
    kfilelistnode = seq64.romdesc.getOrCreateChildWithName("knownfilelist", nullptr);
    txtFTAddr->setText(ROM::hex((uint32)(int)seq64.romdesc.getProperty("ftaddr", 0)));
    int indextype = (int)seq64.romdesc.getProperty("indextype", 1);
    optIndexType1->setToggleState((indextype == 1), dontSendNotification);
    optIndexType2->setToggleState((indextype == 2), dontSendNotification);
    //Load index addresses
    ValueTree index;
    int addr;
    index = kfilelistnode.getChildWithProperty("type", "Audiobank Index");
    if(index.isValid()){ addr = index.getProperty("address", -1);
    }else{ addr = -1; }
    changedIndexAddress("Audiobank Index", addr);
    index = kfilelistnode.getChildWithProperty("type", "Audioseq Index");
    if(index.isValid()){ addr = index.getProperty("address", -1);
    }else{ addr = -1; }
    changedIndexAddress("Audioseq Index", addr);
    index = kfilelistnode.getChildWithProperty("type", "Sample Set Index");
    if(index.isValid()){ addr = index.getProperty("address", -1);
    }else{ addr = -1; }
    changedIndexAddress("Sample Set Index", addr);
    index = kfilelistnode.getChildWithProperty("type", "Instrument Set Index");
    if(index.isValid()){ addr = index.getProperty("address", -1);
    }else{ addr = -1; }
    changedIndexAddress("Instrument Set Index", addr);
    //Refresh screen
    fillFileTable();
    fillKFiles();
}

void FilesPane::fillInstSetBoxes(){
    cbxInstSet1->clear();
    if(seq64.rom.getSize() == 0) return;
    if(!selindex.isValid()) return;
    if(selindex.getProperty("type", "Unsupported").toString() != "Audioseq Index"){
        lblInstSet->setText("Instrument sets (Audioseq Index only):", dontSendNotification);
        return;
    }
    if(isi_addr < 0){
        lblInstSet->setText("No Instrument Set Index defined!", dontSendNotification);
        return;
    }
    if(abi_addr < 0){
        lblInstSet->setText("No Audiobank Index defined!", dontSendNotification);
        return;
    }
    if(abi_count < 0 || abi_count >= 0x100){
        lblInstSet->setText("Invalid inst set count, probably wrong addr for Audiobank Index", dontSendNotification);
        return;
    }
    lblInstSet->setText("Instrument sets:", dontSendNotification);
    ValueTree abk_names = seq64.romdesc.getOrCreateChildWithName("audiobankidx", nullptr);
    String desc;
    ValueTree bank;
    for(int i=0; i<abi_count; i++){
        desc = ROM::hex((uint8)i);
        bank = abk_names.getChildWithProperty("index", i);
        if(bank.isValid()){
            desc += ": " + bank.getProperty("name", "[Unnamed]").toString();
        }
        cbxInstSet1->addItem(desc, cbxInstSet1->getNumItems()+1);
    }
}

bool FilesPane::isKnownFileType(String filetype){
    for(int i=0; i<cbxKFileType->getNumItems(); i++){
        if(cbxKFileType->getItemText(i).equalsIgnoreCase(filetype)) return true;
    }
    return false;
}

void FilesPane::changedIndexAddress(String indextype, int newaddress){
    if(indextype == "Audiobank Index"){
        abi_addr = newaddress;
        if(newaddress < 0 || seq64.rom.getSize() <= abi_addr + 4){
            abi_count = -1;
            return;
        }
        if((int)seq64.romdesc.getProperty("indextype", 1) == 2){
            abi_count = seq64.rom.readHalfWord(abi_addr);
        }else{
            abi_count = seq64.rom.readHalfWord(abi_addr+2);
        }
    }else if(indextype == "Audioseq Index"){
        asi_addr = newaddress;
        if(newaddress < 0 || seq64.rom.getSize() <= asi_addr + 4){
            asi_count = -1;
            return;
        }
        if((int)seq64.romdesc.getProperty("indextype", 1) == 2){
            asi_count = seq64.rom.readHalfWord(asi_addr);
        }else{
            asi_count = seq64.rom.readHalfWord(asi_addr+2);
        }
    }else if(indextype == "Sample Set Index"){
        ssi_addr = newaddress;
        if(newaddress < 0 || seq64.rom.getSize() <= ssi_addr + 4){
            ssi_count = -1;
            return;
        }
        if((int)seq64.romdesc.getProperty("indextype", 1) == 2){
            ssi_count = seq64.rom.readHalfWord(ssi_addr);
        }else{
            ssi_count = seq64.rom.readHalfWord(ssi_addr+2);
        }
    }else if(indextype == "Instrument Set Index"){
        isi_addr = newaddress;
    }
}


//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="FilesPane" componentName=""
                 parentClasses="public Component, public TextEditor::Listener, public TextListModel::Listener"
                 constructorParams="SEQ64&amp; seq64_" variableInitialisers="seq64(seq64_)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff"/>
  <GROUPCOMPONENT name="new group" id="da1838da4937cc20" memberName="groupComponent"
                  virtualName="" explicitFocusOrder="0" pos="0 0 336 448" title="Master File Table"/>
  <LABEL name="new label" id="feac5e6d64dda05e" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="8 16 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Address:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="b0f34b76891a115d" memberName="txtFTAddr"
              virtualName="" explicitFocusOrder="0" pos="80 16 80 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="new label" id="9d8b9b46e68c2983" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="8 392 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Name:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="baf4f79779fe44c6" memberName="txtFileName"
              virtualName="" explicitFocusOrder="0" pos="64 392 264 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="new label" id="5e17f0c7cbf49c52" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="8 416 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Type:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <COMBOBOX name="new combo box" id="a982a2bb18b425a6" memberName="cbxFileType"
            virtualName="" explicitFocusOrder="0" pos="64 416 264 24" editable="0"
            layout="33" items="Unknown&#10;ROM Header&#10;Boot Code&#10;Master File Table&#10;Audiobank&#10;Audioseq&#10;Audiotable&#10;Code&#10;Texture&#10;Shared Assets&#10;Text Data&#10;Actor&#10;Object&#10;Scene&#10;Room&#10;Other"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="f2833c68aa3a69c3" memberName="label4" virtualName=""
         explicitFocusOrder="0" pos="8 368 320 24" edTextCol="ff000000"
         edBkgCol="0" labelText="[Address information]" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <GROUPCOMPONENT name="new group" id="f59a75502f6f9763" memberName="groupComponent2"
                  virtualName="" explicitFocusOrder="0" pos="0 448 336 264" title="Known Files"/>
  <TEXTBUTTON name="new button" id="20b0109f8e92d22a" memberName="btnKFileAdd"
              virtualName="" explicitFocusOrder="0" pos="8 624 40 24" buttonText="Add"
              connectedEdges="2" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="5eceeff61cabc54a" memberName="btnKFileDel"
              virtualName="" explicitFocusOrder="0" pos="48 624 40 24" buttonText="Del"
              connectedEdges="1" needsCallback="1" radioGroupId="0"/>
  <LABEL name="new label" id="3b17daf4620f7036" memberName="label5" virtualName=""
         explicitFocusOrder="0" pos="96 624 47 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Type:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <COMBOBOX name="new combo box" id="dba63b9be0a5c57" memberName="cbxKFileType"
            virtualName="" explicitFocusOrder="0" pos="144 624 184 24" editable="0"
            layout="33" items="Unsupported&#10;Audiobank&#10;Audioseq&#10;Audiotable&#10;Audiobank Index&#10;Audioseq Index&#10;Sample Set Index&#10;Instrument Set Index"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="1756f94b14c6940f" memberName="label6" virtualName=""
         explicitFocusOrder="0" pos="176 656 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Address:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="e1d35d2b85f2de9a" memberName="txtKFileAddr"
              virtualName="" explicitFocusOrder="0" pos="248 656 80 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="new label" id="29eda2beea4f4f73" memberName="label7" virtualName=""
         explicitFocusOrder="0" pos="176 680 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Length:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="f3befab09a65150a" memberName="txtKFileLength"
              virtualName="" explicitFocusOrder="0" pos="248 680 80 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <GROUPCOMPONENT name="new group" id="a707e7b9cb5e40a2" memberName="grpIndex"
                  virtualName="" explicitFocusOrder="0" pos="336 0 424 712" title="Index"/>
  <LABEL name="new label" id="5c4f6c4947dd2650" memberName="lblIndexProps"
         virtualName="" explicitFocusOrder="0" pos="344 88 408 24" edTextCol="ff000000"
         edBkgCol="0" labelText="[Index length, address, etc.]" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="5d02266efa726b59" memberName="label11" virtualName=""
         explicitFocusOrder="0" pos="344 472 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Name:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="d2ccdddf01b27ef0" memberName="txtIEntryName"
              virtualName="" explicitFocusOrder="0" pos="400 472 352 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="new label" id="750191ec030e4bcc" memberName="lblIEntryData"
         virtualName="" explicitFocusOrder="0" pos="344 448 408 24" edTextCol="ff000000"
         edBkgCol="0" labelText="[Entry data]" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="new button" id="c6f7b2138260d81d" memberName="btnLoadEntry"
              virtualName="" explicitFocusOrder="0" pos="344 504 136 24" buttonText="Load Entry"
              connectedEdges="8" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="93eb02f5f765bd07" memberName="btnSaveEntry"
              virtualName="" explicitFocusOrder="0" pos="344 528 136 24" buttonText="Save Entry"
              connectedEdges="4" needsCallback="1" radioGroupId="0"/>
  <GROUPCOMPONENT name="new group" id="9f0f9c0355363fa1" memberName="groupComponent4"
                  virtualName="" explicitFocusOrder="0" pos="344 16 408 72" title="Index Format"/>
  <TOGGLEBUTTON name="new toggle button" id="b9de436f2f2f8a29" memberName="optIndexType1"
                virtualName="" explicitFocusOrder="0" pos="352 32 392 24" buttonText="Word hdr; [addr, length] (SM64, MK64)"
                connectedEdges="0" needsCallback="1" radioGroupId="1" state="1"/>
  <TOGGLEBUTTON name="new toggle button" id="c28e8c6e3b30311f" memberName="optIndexType2"
                virtualName="" explicitFocusOrder="0" pos="352 56 392 24" buttonText="4-word hdr; [addr, length, 2 data] (Zelda, Yoshi)"
                connectedEdges="0" needsCallback="1" radioGroupId="1" state="0"/>
  <LABEL name="new label" id="52709144fcf447d1" memberName="lblInstSet"
         virtualName="" explicitFocusOrder="0" pos="344 560 408 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Instrument sets:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="6d5d89e6ea22ae4c" memberName="label10" virtualName=""
         explicitFocusOrder="0" pos="344 680 40 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Set:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <COMBOBOX name="new combo box" id="eb9c8b0efed24a37" memberName="cbxInstSet1"
            virtualName="" explicitFocusOrder="0" pos="384 680 368 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
