using System;
using System.Collections.Generic;

namespace WebApplication1.Entities;

public partial class Inventory
{
    public int Serial { get; set; }

    public string Isbn { get; set; } = null!;

    public virtual Checkedout? Checkedout { get; set; }

    public virtual Title IsbnNavigation { get; set; } = null!;
}
