package fr.graphics;

import fr.action_listenner.Button_act;

import javax.swing.*;
import java.util.ArrayList;

public class Menu extends JMenu {

    private String mName;
    public JMenu mMenu;
    private ArrayList<Menu_item> JMIlist;


    public Menu(String buttonText[], String name){
        mName = name;
        mMenu = new JMenu(mName);
        JMIlist = new ArrayList<Menu_item>();
        createMenuItem(buttonText);
        actionEvent();

    }
    public Menu(String name){
        mName = name;
        mMenu = new JMenu(mName);

    }

    /**
     * create Item Menu chain , | separator, ¤ without shortcut , by default shortcuts are activated
     * @param buttonText
     */
    private void createMenuItem(String[] buttonText){
        int i = 0;


            while (i < buttonText.length) {

                if (buttonText[i].equals("|")) {
                    mMenu.addSeparator();

                } else if (buttonText[i].startsWith("¤")){

                    Menu_item But = new Menu_item(buttonText[i].substring(1),false);
                    mMenu.add(But.Item);
                    JMIlist.add(But);

                } else {
                    Menu_item But = new Menu_item(buttonText[i],true);

                    mMenu.add(But.Item);
                    JMIlist.add(But);
                }

                i++;
            }

    }

    public ArrayList<Menu_item> getJMIlist() {
        return JMIlist;
    }

    /**
     * Create an action Button
     */
    private void actionEvent() {

             Button_act Action = new Button_act(JMIlist);

    }

}
