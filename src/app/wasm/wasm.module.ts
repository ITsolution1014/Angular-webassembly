import { NgModule } from "@angular/core";
import { BrowserModule } from "@angular/platform-browser";
import { HttpClientModule } from "@angular/common/http";
import { FormsModule } from "@angular/forms";
import { LaddaModule } from "angular2-ladda";

import { HumanizeTimePipe } from "./humanize-time-pipe";

import { Wasm3dCubeComponent } from "./3d-cube/3d-cube.component";

@NgModule({
  declarations: [HumanizeTimePipe, Wasm3dCubeComponent],
  imports: [
    BrowserModule,
    HttpClientModule,
    FormsModule,
    LaddaModule.forRoot({
      style: "zoom-in",
      spinnerSize: 30,
    }),
  ],
})
export class WasmModule {}
