<?php
/**
 * @file
 * Default theme implementation to display a single Drupal page.
 *
 * Available variables:
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 *   least, this will always default to /.
 * - $directory: The directory the template is located in, e.g. modules/system
 *   or themes/garland.
 * - $is_front: TRUE if the current page is the front page.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to main-menu administration pages.
 *
 * Site identity:
 * - $front_page: The URL of the front page. Use this instead of $base_path,
 *   when linking to the front page. This includes the language domain or
 *   prefix.
 * - $logo: The path to the logo image, as defined in theme configuration.
 * - $site_name: The name of the site, empty when display has been disabled
 *   in theme settings.
 * - $site_slogan: The slogan of the site, empty when display has been disabled
 *   in theme settings.
 *
 * Navigation:
 * - $main_menu (array): An array containing the Main menu links for the
 *   site, if they have been configured.
 * - $secondary_menu (array): An array containing the Secondary menu links for
 *   the site, if they have been configured.
 * - $breadcrumb: The breadcrumb trail for the current page.
 *
 * Page content (in order of occurrence in the default page.tpl.php):
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title: The page title, for use in the actual HTML content.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 * - $messages: HTML for status and error messages. Should be displayed
 *   prominently.
 * - $tabs (array): Tabs linking to any sub-pages beneath the current page
 *   (e.g., the view and edit tabs when displaying a node).
 * - $action_links (array): Actions local to the page, such as 'Add menu' on the
 *   menu administration interface.
 * - $feed_icons: A string of all feed icons for the current page.
 * - $node: The node object, if there is an automatically-loaded node
 *   associated with the page, and the node ID is the second argument
 *   in the page's path (e.g. node/12345 and node/12345/revisions, but not
 *   comment/reply/12345).
 *
 * Regions:
 * - $page['help']: Dynamic help text, mostly for admin pages.
 * - $page['content']: The main content of the current page.
 * - $page['sidebar_first']: Items for the first sidebar.
 * - $page['sidebar_second']: Items for the second sidebar.
 * - $page['header']: Items for the header region.
 * - $page['footer']: Items for the footer region.
 *
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see template_process()
 */
?>

<div id="wrapper">
  <header id="header" role="banner">
    <?php if ($logo): ?><div id="logo"><a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>"><img src="<?php print $logo; ?>"/></a></div><?php endif; ?>
    <div id="feedback-container"><a id="feedback" href="/"></a></div>
    <div id="site-info">
      <div id="phone-number"><span>CALL US <br>1-702-659-8829</span></div>
      <div id="social-icons">
        <ul>
          <li><a id="twiiter-icon" href="https://twitter.com/goskoot"></a></li>
          <li><a  id="facebook-icon" href=""></a></li>
          <li><a  id="googleplus-icon" href=""></a></li>
          <li><a  id="linkedin-icon" href=""></a></li>
        </ul>
      </div>
    </div>
    <div class="clear"></div>
    <div id="nav-before"></div>
    <nav id="main-menu"  role="navigation">
      <a class="nav-toggle" href="#">Navigation</a>
      <div class="menu-navigation-container">
        <?php 
        if (module_exists('i18n_menu')) {
          $main_menu_tree = i18n_menu_translated_tree(variable_get('menu_main_links_source', 'main-menu'));
        } else {
          $main_menu_tree = menu_tree(variable_get('menu_main_links_source', 'main-menu'));
        }
        print drupal_render($main_menu_tree);
        ?>
      </div>
      <div class="clear"></div>
    </nav><!-- end main-menu -->
    <div id="nav-after"></div>
  </header>

  
  <div id="container">
   <?php if ($page['header']): ?>
   <div id="head">
    <?php print render($page['header']); ?>
   </div>
   <div class="clear"></div>
   <?php endif; ?>

    <div class="content-sidebar-wrap">

    <div id="content">
      <section id="post-content" role="main">
        <?php print $messages; ?>
        <?php if ($page['content_top']): ?><div id="content_top"><?php print render($page['content_top']); ?></div><?php endif; ?>
        <?php print render($title_prefix); ?>
        <?php if ($title): ?><h1 class="page-title"><?php //print $title; ?></h1><?php endif; ?>
        <?php print render($title_suffix); ?>
        <?php if (!empty($tabs['#primary'])): ?><div class="tabs-wrapper"><?php print render($tabs); ?></div><?php endif; ?>
        <?php print render($page['help']); ?>
        <?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>
        <?php print render($page['content']); ?>
      </section> <!-- /#main -->
    </div>
  
    <?php if ($page['sidebar_first']): ?>
      <aside id="sidebar-first" role="complementary">
        <?php print render($page['sidebar_first']); ?>
      </aside>  <!-- /#sidebar-first -->
    <?php endif; ?>
  
    </div>

    <?php if ($page['sidebar_second']): ?>
      <aside id="sidebar-second" role="complementary">
        <?php print render($page['sidebar_second']); ?>
      </aside>  <!-- /#sidebar-first -->
    <?php endif; ?>
  
    <div class="clear"></div>
  </div> 

</div>
<div id="footer-line"></div>
<div id="star"></div>
<div id="footer-wrapper">
  <div id="footer">
  <?php print render($page['footer']) ?>
  </div>
</div>
