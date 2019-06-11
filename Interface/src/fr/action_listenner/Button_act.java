package fr.action_listenner;

import fr.graphics.Buttons;
import fr.graphics.Menu_item;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;

public class Button_act implements ActionListener {
	
    public Button_act(ArrayList<Buttons> list, ArrayList<Menu_item> Menulist){
    	
        for ( Buttons f: list){
            f.mButton.addActionListener(this);
        }
        
        for ( Menu_item h: Menulist){
            h.Item.addActionListener(this);
        }
    }
    
    public Button_act(ArrayList<Menu_item> list){
    	
        for ( Menu_item f: list){
            f.Item.addActionListener(this);
        }
    }
    
    public Button_act(Buttons btn){
    	
    	btn.mButton.addActionListener(this);
    }
    
    public Button_act(ArrayList<Menu_item> Menulist, ActionListener e) {
    	 for ( Menu_item f: Menulist){
             f.Item.addActionListener(e);
         }
    }

	@Override
	public void actionPerformed(ActionEvent arg0) {
		
	}
 

	

}
