ShipSim : A Ship Design Program
Version : 0.3a
--------------------------------------------

ShipSim is a program for amateur ship designers to design "what-if" and "never built" warships from 1850 to the modern day. You may design for ships before 1850, but the accuracy is not verified.

ShipSim is a program rooted in formulas and calculations used by professional Naval Architects and structural engineers. Ship Sim is meant for high speed first attempts at ship design and is thus not intended or recommended to be the sole program relied upon in a design that will be built.

ShipSim relies a wide array of estimation formulas and techniques to acquire it's results, so it's output should never be treated as fact.

ShipSim will write a very detailed output report to the console and create/overwrite the file "Report.txt" in the same directory. "Report.txt" is formatted as a table in bbcode [tag][/tag] standard but can be easily converted to a standard HTML table by replacing all the "[" with "<" and "]" with ">".

-------------------------------------------

ShipSim is a free software, as in free beer not free speech. You may redistribute it freely, but may not modify it or use it commercially. If you wish to modify or use it commercially, you will need to speak to me, the creator.

ShipSim is licensed under the Creative Commons Attribution-NonCommercial-NoDerivs 3.0 Unported License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-nd/3.0/.

-------------------------------------------

ShipSim	author

Kelsey Yuen
mailto:ky.staedler@gmail.com

As of 9/24/2013 you should be able to find me on www.navalism.org, wesworld.jk-clan.de under the pseudonym "Logi". I also frequent #WesWorld on irc.nightstar.net. Feel free to send me feedback via IRC, or PMs on the forums. You can also email me at my listed email address.

Since I am only a participant in the Navalism and Wesworld boards, please contact me by email first and only the other options when it has been exhausted. If,  however, you are a member of Navalism or Wesworld, free feel to contact me through any of the options.

-------------------------------------------

NOMENCLATURE

Lpp					-	Length between perpendiculars
Bwl					-	Beam at waterline
D					- 	Draft (the distance from keel to waterline)
fB					-	Freeboard (the distance from the waterline to the top of the hull)
cB					-	Block Coefficient
Vk					-	Max Speed of ship in knots
Vc					-	Cruise Speed of ship in knots
Range				-	Endurance at cruise speed
Lspus				-	The length of the superstructure
e					- 	Length of the entrance (the portion extending from the maximum area section, or from the fore end of the parallel middle-body,
						to the forward extremity of the underwater body)
r					-	Length of the run (the portion extending from the maximum area section, or from the after end of the parallel middlebody,
						to the after extremity of the underwater body)
Efficiency			-	The total efficiency of the system, i.e. Propeller, Transmission, Shaft, Engine, etc.
Service Allowance	-	A modifier based on accepted values by Shipping companies on the amount of power needed to reach the design speed in different regions
						and routes of travel
Froude Number		-	A value used as reference in rules of thumb which discourage ships with froude numbers in certain ranges
Z					- 	The number of propeller blades on each propeller (usually this is 3-5 and a higher than 5 number is difficult and requires precise machining)
Faa					-	The shape of the aftbody, either 'U', 'V', or 'N'
						'N' is a normal hull shape and 'U', 'V' are hull shapes like the letters
dB					-	Double bottom
T					-	Thickness
Ends Deck			- 	The portion of the deck not covered by the main deck armor