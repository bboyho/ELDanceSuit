Wireless Controlled EL Dance Suits
-------------------

This code will be used to wirelessly control 2x 3 meters of EL Wire attached to a dancer's hoodie and pants
for a performance with Streetside Studio's bboys/bgirls. In less than 3 months with my usual day job, teaching, and training. 42 meters (~1,653.5 inches) of manual hand sewing white EL wire to hoodies and pants, custom connectors, soldering, a little coding with Arduino, 8x XBees configured as point-to-multipoint network, 7x enclosures attached to everyone's hip, straps, a wireless glove, choreographing, and editing parts of a track together.

<table class="table table-hover table-striped table-bordered">
  <tr align="center">
    <td colspan="3"><a href="https://learn.sparkfun.com/tutorials/wireless-controlled-wearable-el-wire-dance-suit"><img src="https://cdn.sparkfun.com/assets/learn_tutorials/7/7/2/Wireless_Controlled_Wearable_EL_Wire_Dance_Suit_Ripple.gif" title="Wireless EL Dance Suit Demo"></a></td>
  </tr>
  <tr align="center">
    <td><a href="https://learn.sparkfun.com/tutorials/wireless-controlled-wearable-el-wire-dance-suit/securing-the-electronics"><img src="https://cdn.sparkfun.com/assets/learn_tutorials/7/7/2/Cardboard_Enclosures_Wireless_Controlled_EL_Sequencers.jpg" title="Enclosure" width="85%"></a></td>
   <td><a href="https://learn.sparkfun.com/tutorials/wireless-controlled-wearable-el-wire-dance-suit/stress-testing-in-the-field"><img src="https://cdn.sparkfun.com/assets/home_page_posts/2/9/1/0/Dancers_EL-Wire_Suits.jpg" title="Performance Day" width="85%"></a></td>
  <td><a href="https://www.sparkfun.com/news/3181"><img src="https://cdn.sparkfun.com/assets/home_page_posts/3/1/8/1/Light_Painting_EL_LED_4222.jpg" title="Light Painting"></a></td>
  </tr>
</table>

Repository Contents
-------------------
**<> Code**
- /[XBee_ELSequencer](https://github.com/bboyho/ELDanceSuit/tree/master/Arduino/EL_XBeeWirelessControl/XBee_ELSequencer)
- /[XBee_ELSequencer_Controller](https://github.com/bboyho/ELDanceSuit/tree/master/Arduino/EL_XBeeWirelessControl/XBee_ELSequencer_Controller)

Documentation
-------------------

* Tutorials
  * [Exploring XBees and XCTU](https://learn.sparkfun.com/tutorials/exploring-xbees-and-xctu)
  * [SparkFun EL Sequencer Hookup Guide](https://learn.sparkfun.com/tutorials/el-sequencerescudo-dos-hookup-guide)
    * [GitHub Repository for EL Sequencer](https://github.com/sparkfun/EL_Sequencer/tree/master)
  * [Wireless Controlled Wearable EL Wire Dance Suit
](https://learn.sparkfun.com/tutorials/wireless-controlled-wearable-el-wire-dance-suit/)
    * [EL Wire Hoodie](https://learn.sparkfun.com/tutorials/el-wire-hoodie)
    * [EL Wire Pants](https://learn.sparkfun.com/tutorials/el-wire-pants)
    * [Wireless Glove Controller](https://learn.sparkfun.com/tutorials/wireless-glove-controller)
    * [Modifying Your EL Wire Inverter](https://learn.sparkfun.com/tutorials/modifying-your-el-wire-inverter)
    * [How to Make a Custom EL Wire Extension Cable](https://learn.sparkfun.com/tutorials/how-to-make-a-custom-el-wire-extension-cable)
* SparkFun Blog
  * [Enginursday: Building a Wireless EL Wire Dance Suit, Part 1](https://www.sparkfun.com/news/2910)
  * [Enginursday: Building a Wireless EL Wire Dance Suit, Part 2](https://www.sparkfun.com/news/2963)
  * [Enginursday: Building a Wireless EL Wire Dance Suit, Part 3](https://www.sparkfun.com/news/3115)
  * [Enginursday: Light Painting with EL Wire and an LED](https://www.sparkfun.com/news/3181)
* Instagram: bobbybrownrice - Demos and Project Images
  * [Test 1 - Wireless Test](https://www.instagram.com/p/BT502rzF0ND/)
  * [Test 2 - Wireless Test in the Dark](https://www.instagram.com/p/BT51mbBFOCs/)
  * [Test 3 - Wireless Glove Test ](https://www.instagram.com/p/BT-tP7RFKn8/)
  * [Test 4 - Wireless Glove Test Prammed to the Beat](https://www.instagram.com/p/BUDyLCmlEUp/)
  * [Enclosure](https://www.instagram.com/p/BUDzBpvFZDb/)
  * [Performance Day](https://www.instagram.com/p/BUDzvJ5Fu8r/)
  * [Demo Video](https://www.instagram.com/p/BUD_RaelsrU/)
  * [Light Painting](https://www.instagram.com/p/BUiiFTGFC9k/)

XBee Series 1, Pro:  Point to Multipoint Configuration
-------------------

[Digi Tutorial: XBee 802.15.4 (i.e. Wireless Serial)](http://examples.digi.com/get-started/basic-xbee-802-15-4-chat/ )

* Master XBee
  * CH = C
  * ID = 3333
  * DH = 0
  * DL = FFFF (2)
  * MY = 1

* Slave XBee
  * CH = C
  * ID = 3333
  * DH = 0
  * DL = 1 <- point to Master "MY"
  * MY = 2 <- Slave "MY", make it unique in the network.

License Information
-------------------

This project is _**open source**_! 

Please review the [LICENSE.md file](https://github.com/bboyho/ELSuit/blob/master/LICENSE.md) for license information. 

Distributed as-is; no warranty is given.
