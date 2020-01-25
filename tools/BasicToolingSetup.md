# Basic Tooling Setup

**tl;dr**: Get [git](https://git-scm.com/), [Node.JS](https://nodejs.org/en/) and [DotNetCore](https://dotnet.microsoft.com/download/) and read about [VSCode](VisualStudioCode.md).

## git

Git is a free command line based version control system. As it is distributed, it can be used to hold multiple installations of the same repo in sync. It is also used to push changes to servers - in my case some Raspberries, GitHub or Azure. Ahh - and it manages file versions too.

[Download it from here](https://git-scm.com/).

The main features are nicely covered via VSCode and its GitLens extension. It would not be amiss to know the main commands either.

## Node.JS

Most web projects can be setup using the [Node package manager](https://www.npmjs.com/) npm, which is part of [Node.js](https://nodejs.org/en/), a JavaScript runtime built on Chrome's JavaScript engine.

[Download the most recent LTS version](https://nodejs.org/en/) (12.x) and keep the default settings.

Check the installed version with `npm -v`.

## DotNet (Core) SDK

For lightweight "real programming" I mainly develop in C#. As **DotNet Core 3.1** can easily be executed in Linux based Docker container too (Raspberry Pi!), this version of the runtime is my preferred choice.

Get it via the cool website <dot.net>, click [Download] and [choose the Core SDK](https://dotnet.microsoft.com/download/dotnet-core/3.1) to build apps.

Check the installed versions of the SDK or runtime with `dotnet --info`.

No longer required versions can be removed via the "Apps and Features" section of the windows settings. Right-click the Windows start button and choose the first entry from the context menu; then search for "SDK".

For more heavy stuff the full **.Net Framework 4.8** is used via the free [Visual Studio Community IDE](https://visualstudio.microsoft.com/de/thank-you-downloading-visual-studio/?sku=Community&rel=16). But this then is a multi gigabyte setup - at leastthe IDE already contains the SDK.
