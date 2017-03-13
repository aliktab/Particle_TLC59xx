# TLC59xx

*Particle Library for the TLC59xx chip series*

Particle library to control TLC59xx chip series, supports connection via any hardware SPI.
Currently supports the only TLC59711 chip. Support for the TLC5947 is planned.

## Usage

Connect any TLC59xx hardware, add the TLC59xx library to your project and follow this simple example:

```
#include "TLC59xx.h"
TLC59711 led_array(1, SPI);

void setup()
{
  led_array.begin();
  led_array.set_BC(0x30, 0x7f, 0x03);
  led_array.clear();

  for (int i = 0; i < 12; i++)
    led_array.set_PWM(i, TLC59711_MAX_PWM_VAL);

  led_array.show_data();
}

void loop()
{
}
```

See the [examples](examples) folder for more details.

## Contributing

Here's how you can make changes to this library and eventually contribute those changes back.

To get started, [clone the library from GitHub to your local machine](https://help.github.com/articles/cloning-a-repository/).

Change the name of the library in `library.properties` to something different. You can add your name at then end.

Modify the sources in <src> and <examples> with the new behavior.

To compile an example, use `particle compile examples/usage` command in [Particle CLI](https://docs.particle.io/guide/tools-and-features/cli#update-your-device-remotely) or use our [Desktop IDE](https://docs.particle.io/guide/tools-and-features/dev/#compiling-code).

After your changes are done you can upload them with `particle library upload` or `Upload` command in the IDE. This will create a private (only visible by you) library that you can use in other projects. Do `particle library add NeoRingDsp_myname` to add the library to a project on your machine or add the NeoRingDsp_myname library to a project on the Web IDE or Desktop IDE.

At this point, you can create a [GitHub pull request](https://help.github.com/articles/about-pull-requests/) with your changes to the original library.

If you wish to make your library public, use `particle library publish` or `Publish` command.

## LICENSE
Copyright (C) 2014 Alik <aliktab@gmail.com> All rights reserved.

This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with this library; if not, write to the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
