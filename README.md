# ShootMeToTheMoooon

Shoot me to the moon,  
let me play among `<std::fstream>`
And let me see what V is like  
Between Earth aaaand its moon..   
In other words, find an x_0  
In other words, baby, y''(t) =  p(t)y'(t) + q(t)y(t) + r(t)  


## Aufbau
Das Repository besteht aus dem *Simulation* und dem *Bericht* Ordner. Es entählt keine kompilierten Versionen vom Code, jedoch vom LaTeX Dokument des Berichtes, da hierzu ein seperates Paket vonnöten ist.

## Ressourcen 
Das zur PDF Kompilierung nötige LaTeX Paket ist unter https://github.com/unb3rechenbar/UniLaTeXPackage.git frei abrufbar. Um das Paket in den Kompilierprozess einzubinden, setze die Systemvariable TEXINPUTS entsprechend:

```
export TEXINPUTS=/path/to/package:$TEXINPUTS
```

(getestet unter macOS und Linux).