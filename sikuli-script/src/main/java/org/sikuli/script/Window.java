package org.sikuli.script;

public class Window extends Region {
  private String name;
  private long id;

  public Window(String name, long id, int x, int y, int w, int h) {
    super(x, y, w, h);
    this.name = name;
    this.id = id;
  }

  public void refresh() {
    Window w;
    if (id == -1) w = Env.getOSUtil().getWindow(name);
    else w = Env.getOSUtil().getWindowById(id);
    this.name = w.name;
    this.id = w.id;
    this.x = w.x;
    this.y = w.y;
    this.w = w.w;
    this.h = w.h;
  }

  public String getName() {
    return name;
  }

  public long getID() {
    return id;
  }

  public String toString() {
    return super.toString()+", N:"+name;
  }
}
