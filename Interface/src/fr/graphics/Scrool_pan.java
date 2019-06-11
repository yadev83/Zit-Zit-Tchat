package fr.graphics;

import javax.swing.*;

import fr.xmleditor.XmlTextPane;

import java.awt.*;

public class Scrool_pan extends JScrollPane {
    public  JScrollPane mPan;
    //public Text_area mText;
    public XmlTextPane xmlTextPane;
    
    public Scrool_pan(){
    	//Text_area newtexte = new Text_area();
    	//mText = newtexte;
    	//mText = new Text_area();
        //mPan = new JScrollPane(mText);
        xmlTextPane = new XmlTextPane();
    	mPan = new JScrollPane(xmlTextPane);
    }
}
