#include <Espalexa.h>

void dl(EspalexaDevice* dev);
void dlf(EspalexaDevice* dev);

Espalexa espalexa;

void setupAlexa() {
  espalexa.addDevice("Wardrobe Lights", dl, EspalexaDeviceType::color); // Color device
  espalexa.addDevice("Wardrobe Lights Fade", dlf, EspalexaDeviceType::onoff); // Non-dimmable device
  
  espalexa.begin();
}

void dl(EspalexaDevice* d) {
  if (d == nullptr) return;

  lights->setRGB(d->getRGB());
  lights->setBrightness(d->getValue() / (float) 2.55);

  if (d->getState() != lights->getState())
    lights->setState(d->getState());  
}

void dlf(EspalexaDevice* d) {
  if (d == nullptr) return;

  lights->setMode(d->getValue() ? PERLIN : SOLID_COLOR);
}

void syncValuesAlexa() {
  espalexa.getDevice(0)->setState(lights->getState());
  espalexa.getDevice(0)->setValue(map(lights->getTargetBrightness(), 0, 100, 0, 255));
  espalexa.getDevice(0)->setColor(lights->getR(), lights->getG(), lights->getB());

  espalexa.getDevice(1)->setState(lights->getMode());
}
