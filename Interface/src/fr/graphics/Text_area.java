package fr.graphics;

import javax.swing.*;
import java.awt.*;

public class Text_area extends JTextArea {
    //public String mContent;
    public JTextArea mArea;

    public Text_area(String content){
        //mContent = content;
        mArea = new JTextArea(content);
        mArea.setFont(new Font("Serif", Font.ITALIC, 16));
    }
    
    public Text_area () {
        //mContent = "";
        mArea = new JTextArea("");
        mArea.setFont(new Font("Serif", Font.ITALIC, 16));
        mArea.setEditable(false);
    }
    
    
    public final String highlight(String source)
    {
        source = source.replaceAll("<([^>/]*)/>", "&lt;~blue~$1~/~/&gt;");
        source = source.replaceAll("<([^>]*)>", "&lt;~blue~$1~/~&gt;");
        source = source.replaceAll("([\\w]+)=\"([^\"]*)\"", "~red~$1~/~~black~=\"~/~~green~$2~/~~black~\"~/~");
        source = source.replaceAll("~([a-z]+)~", "<span style=\"color: $1;\">");
        source = source.replace("~/~", "</span>");
        return source;
    }
}
