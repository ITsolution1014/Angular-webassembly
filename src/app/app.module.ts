import { BrowserModule } from "@angular/platform-browser";
import { NgModule } from "@angular/core";

import { AppRoutingModule } from "./app-routing.module";
import { WasmModule } from "./wasm/wasm.module";

import { AppComponent } from "./app.component";

@NgModule({
  imports: [BrowserModule, AppRoutingModule, WasmModule],
  declarations: [AppComponent],
  bootstrap: [AppComponent],
})
export class AppModule {}
