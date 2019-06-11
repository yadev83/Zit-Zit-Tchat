package fr.graphics;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;


import javax.swing.*;

import fr.action_listenner.GestionFichier;
import fr.parseur.Parseur_launch;
import fr.action_listenner.Button_act;


/**
 *
 */
public class Frame extends GestionFichier implements ActionListener, KeyListener {
	public Scrool_pan mEditCode;
	public Dessin mDessin;
	public Parseur_launch mParse;
	public Fenetre principale;
	public Panel centerPan, westPan;
	public JTextField erorPan;
	private boolean StateAutoRefresh = false, StateFullScreen = false;
	private String version = "Version: Beta 0.3";

	
	public Frame () {
		
		mEditCode = new Scrool_pan();
		mDessin = new Dessin();
		erorPan = new JTextField();
	}


	/**
	 * Create all the dependencies for my programme
	 */
	public void runFrame ()  {
			
			principale = new Fenetre("ValouML", "src/assets/pictures/logo-app.png");
		
			// Déclaration des array
	        String Item[][] = {{"Ouvrir", "Nouveau", "Sauvegarder", "Exporter", "|", "Quitter"}, {"Refresh", "¤Auto-Refresh","|", "Full-Screen"}, {"¤Version", "¤Auteur"}};;
	        String nomMenu[] = {"File","Edition","About"};
	        
	        Menu_bar Bar = new Menu_bar(nomMenu, Item, "moi");

	        //action listener
	        Button_act B1 = new Button_act(Bar.getMListI(0).getJMIlist(),this);
	        Button_act B2 = new Button_act(Bar.getMListI(1).getJMIlist(),this);
			Button_act B3 = new Button_act(Bar.getMListI(2).getJMIlist(),this);

			//panel create
			mEditCode.xmlTextPane.addKeyListener(this);
			centerPan = new Panel(1,1);
			westPan= new Panel(2,1);

			//editor background
			mEditCode.xmlTextPane.setOpaque(true);
			mEditCode.xmlTextPane.setBackground(Color.decode("#263238"));
			mEditCode.xmlTextPane.setCaretColor(Color.white);

			// Ajout des composants
			westPan.mPan.add(mEditCode.mPan,"North");
			centerPan.mPan.add(mEditCode.mPan, "West");
			centerPan.mPan.add(mDessin, "East");
			erorPan.setEditable(false);

			//ajout dans la Frame principal
			principale.contentPane.add(centerPan.mPan, "Center");
			principale.contentPane.add(erorPan,"South");


			principale.setJMenuBar(Bar.mBar);
	        principale.setVisible(true);
	}


	
	public void actionPerformed(ActionEvent e) {
		String cmd = e.getActionCommand();
		
		if(cmd.equals("Quitter")) {
			quitFile(mEditCode.xmlTextPane);
		} else if(cmd.equals("Ouvrir")) {
			openXMLFile(mEditCode.xmlTextPane,mDessin,mParse,principale);
		} else if(cmd.equals("Nouveau")) {
			newFile(mEditCode.xmlTextPane,mDessin,principale);
		} else if(cmd.equals("Sauvegarder")) {
			registerXMLFile(mEditCode.xmlTextPane,principale);
		} else if(cmd.equals("Exporter")) {
			exportDessin(mDessin);
		} else if(cmd.equals("Refresh")) {

			mParse = new Parseur_launch(mEditCode.xmlTextPane.getText());
			mDessin.refreshParseur(mParse.par.getList());
			erorPan.setText(mParse.getParseurEror());

			
		}else if (cmd.equals("Auto-Refresh")){
			if (StateAutoRefresh){
				StateAutoRefresh = false;
			}else {
				StateAutoRefresh = true;
			}

		} else if (cmd.equals("Full-Screen")){

			if (StateFullScreen){
				StateFullScreen = false;
				centerPan.mPan.add(mEditCode.mPan, "West");
				centerPan.mPan.add(mDessin, "East");
				principale.contentPane.add(centerPan.mPan, "Center");
				principale.setVisible(true);

			}else {
				StateFullScreen = true;
				principale.contentPane.remove(centerPan.mPan);
				principale.contentPane.add(mDessin,"Center");
				principale.setVisible(true);


			}

		} else if (cmd.equals("Version")){
			JOptionPane.showMessageDialog((Component) e.getSource(), version,"Version", JOptionPane.INFORMATION_MESSAGE);
		}else if (cmd.equals("Auteur")){
			JOptionPane.showMessageDialog((Component) e.getSource(), "ValouML editor by Valentin Bru","Auteur", JOptionPane.INFORMATION_MESSAGE);

		} else {
			System.err.println(cmd);
		}
	}

	@Override
	public void keyTyped(KeyEvent e) {

	}

	@Override
	public void keyPressed(KeyEvent e) {

	}

	@Override
	public void keyReleased(KeyEvent e) {
		if (StateAutoRefresh ){
			mParse = new Parseur_launch(mEditCode.xmlTextPane.getText());
			mDessin.refreshParseur(mParse.par.getList());
			erorPan.setText(mParse.getParseurEror());
		}

	}
}

