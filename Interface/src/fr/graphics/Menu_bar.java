package fr.graphics;

import javax.swing.*;
import java.util.ArrayList;

public class Menu_bar extends JMenuBar {
    private String mName;
    public JMenuBar mBar;
    private ArrayList<Menu> Mlist;

    public  Menu_bar(String name){mName = name; mBar = new JMenuBar();}
    public Menu_bar(String menuItemText[] ,String buttonText[][], String name){
        mName = name;
        mBar = new JMenuBar();
        Mlist = new ArrayList<Menu>();
        createMenu(menuItemText,buttonText);
    }

    private void createMenu(String[] menuItemText, String[][] buttonText){

        for (int i = 0; i < menuItemText.length ; i++ ){
            Menu menuName = new Menu(buttonText[i], menuItemText[i]);
            mBar.add(menuName.mMenu);
            Mlist.add(menuName);

        }

    }

    public ArrayList<Menu> getMlist() {
        return Mlist;
    }
    
    public Menu getMListI(int n) {
    	return Mlist.get(n);
    }

    public String getmName() {
        return mName;
    }
}
