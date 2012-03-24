package org.sikuli.script;

public class Window extends Region {
  private String name;

  public Window(String name, int x, int y, int w, int h) {
    super(x, y, w, h);
    this.name = name;
  }

  public String getName() {
    return name;
  }

  public String toString() {
    return super.toString()+", N:"+name;
  }
}
